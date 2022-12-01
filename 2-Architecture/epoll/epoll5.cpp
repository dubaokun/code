/*******************************************************************************
* Copyright (C) 2001-2004 Vintela, Inc. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
*  - Neither the name of Vintela, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL Vintela, Inc. OR THE CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/**
 * @author Jon Carey
 * @author Dan Nuffer
 */

#include "BLOCXX_config.h"
#include "Select.hpp"
#include "AutoPtr.hpp"
#include "Assertion.hpp"
#include "Thread.hpp" // for testCancel()

#if defined(BLOCXX_WIN32)
#include <cassert>
#endif

extern "C"
{

#ifndef BLOCXX_WIN32
 #ifdef BLOCXX_HAVE_SYS_EPOLL_H
  #include <sys/epoll.h>
 #endif
 #if defined (BLOCXX_HAVE_SYS_POLL_H)
  #include <sys/poll.h>
 #endif
 #if defined (BLOCXX_HAVE_SYS_SELECT_H)
  #include <sys/select.h>
 #endif
#endif

#ifdef BLOCXX_HAVE_SYS_TIME_H
 #include <sys/time.h>
#endif

#include <sys/types.h>

#ifdef BLOCXX_HAVE_UNISTD_H
 #include <unistd.h>
#endif

#include <errno.h>
}

namespace BLOCXX_NAMESPACE
{

namespace Select
{
#if defined(BLOCXX_WIN32)
//////////////////////////////////////////////////////////////////////////////
int
selectRW(SelectObjectArray& selarray, UInt32 ms)
{
	int rc;
	size_t hcount = static_cast<DWORD>(selarray.size());
	AutoPtrVec<HANDLE> hdls(new HANDLE[hcount]);

	size_t handleidx = 0;
	for (size_t i = 0; i < selarray.size(); i++, handleidx++)
	{
		if(selarray[i].s.sockfd != INVALID_SOCKET
			&& selarray[i].s.networkevents)
		{
			::WSAEventSelect(selarray[i].s.sockfd, 
				selarray[i].s.event, selarray[i].s.networkevents);
		}
				
		hdls[handleidx] = selarray[i].s.event;
	}

	DWORD timeout = (ms != ~0U) ? ms : INFINITE;
	DWORD cc = ::WaitForMultipleObjects(hcount, hdls.get(), FALSE, timeout);

	assert(cc != WAIT_ABANDONED);

	switch (cc)
	{
		case WAIT_FAILED:
			rc = Select::SELECT_ERROR;
			break;
		case WAIT_TIMEOUT:
			rc = Select::SELECT_TIMEOUT;
			break;
		default:
			rc = cc - WAIT_OBJECT_0;
			
			// If this is a socket, set it back to 
			// blocking mode
			if(selarray[rc].s.sockfd != INVALID_SOCKET)
			{
				if(selarray[rc].s.networkevents
					&& selarray[rc].s.doreset == false)
				{
					::WSAEventSelect(selarray[rc].s.sockfd, 
						selarray[rc].s.event, selarray[rc].s.networkevents);
				}
				else
				{
					// Set socket back to blocking
					::WSAEventSelect(selarray[rc].s.sockfd, 
						selarray[rc].s.event, 0);
					u_long ioctlarg = 0;
					::ioctlsocket(selarray[rc].s.sockfd, FIONBIO, &ioctlarg);
				}
			}
			break;
	}

	if( rc < 0 )
		return rc;

	int availableCount = 0;
	for (size_t i = 0; i < selarray.size(); i++)
	{
		if( WaitForSingleObject(selarray[i].s.event, 0) == WAIT_OBJECT_0 )
		{
			if( selarray[i].waitForRead )
				selarray[i].readAvailable = true;
			if( selarray[i].waitForWrite )
				selarray[i].writeAvailable = true;
			++availableCount;
		}
		else
		{
			selarray[i].readAvailable = false;
			selarray[i].writeAvailable = false;
		}
	}
	return availableCount;
}


#else

//////////////////////////////////////////////////////////////////////////////
// epoll version
int
selectRWEpoll(SelectObjectArray& selarray, UInt32 ms)
{
#ifdef BLOCXX_HAVE_SYS_EPOLL_H
	int lerrno = 0, ecc = 0;
	int timeout;
	AutoPtrVec<epoll_event> events(new epoll_event[selarray.size()]);
	int epfd = epoll_create(selarray.size());
	if(epfd == -1)
	{
		if (errno == ENOSYS) // kernel doesn't support it
		{
			return SELECT_NOT_IMPLEMENTED;
		}
		// Need to return something else?
		return Select::SELECT_ERROR;
	}

	UInt32 const read_events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
	UInt32 const write_events = EPOLLOUT | EPOLLERR | EPOLLHUP;
	for (size_t i = 0; i < selarray.size(); i++)
	{
		BLOCXX_ASSERT(selarray[i].s >= 0);
		selarray[i].readAvailable = false;
		selarray[i].writeAvailable = false;
		selarray[i].wasError = false;
		events[i].data.u32 = i;
		events[i].events = 0;
		if(selarray[i].waitForRead)
		{
			events[i].events |= read_events;
		}
		if(selarray[i].waitForWrite)
		{
			events[i].events |= write_events;
		}

		if(epoll_ctl(epfd, EPOLL_CTL_ADD, selarray[i].s, &events[i]) != 0)
		{
			int errnum = errno;
			::close(epfd);
			// Need to return something else?
			return errnum == EPERM ? SELECT_NOT_IMPLEMENTED : SELECT_ERROR;
		}
	}

	// here we spin checking for thread cancellation every so often.
	const Int32 loopMicroSeconds = 100 * 1000; // 1/10 of a second
	timeval now, end;
	gettimeofday(&now, NULL);
	end = now;
	end.tv_sec  += ms / 1000;
	end.tv_usec += (ms % 1000) * 1000;

	while ((ecc == 0) && ((ms == INFINITE_TIMEOUT) || (now.tv_sec < end.tv_sec)
		 || ((now.tv_sec == end.tv_sec) && (now.tv_usec <= end.tv_usec))))
	{
		timeval tv;
		tv.tv_sec = end.tv_sec - now.tv_sec;
		if (end.tv_usec >= now.tv_usec)
		{
			tv.tv_usec = end.tv_usec - now.tv_usec;
		}
		else
		{
			tv.tv_sec--;
			tv.tv_usec = 1000000 + end.tv_usec - now.tv_usec;
		}

		if ((tv.tv_sec != 0) 
			|| (tv.tv_usec > loopMicroSeconds) || (ms == INFINITE_TIMEOUT))
		{
			tv.tv_sec = 0;
			tv.tv_usec = loopMicroSeconds;
		}

		timeout = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		Thread::testCancel();
		ecc = epoll_wait(epfd, events.get(), selarray.size(), timeout);
		lerrno = errno;
		Thread::testCancel();
		gettimeofday(&now, NULL);
	}

	::close(epfd);
	if (ecc < 0)
	{
		return (lerrno == EINTR) ? Select::SELECT_INTERRUPTED : Select::SELECT_ERROR;
	}
	if (ecc == 0)
	{
		return Select::SELECT_TIMEOUT;
	}

	for(int i = 0; i < ecc; i++)
	{
		SelectObject & so = selarray[events[i].data.u32];
		so.readAvailable = so.waitForRead && (events[i].events & read_events);
		so.writeAvailable = so.waitForWrite && (events[i].events & write_events);
	}

	return ecc;
#else
	return SELECT_NOT_IMPLEMENTED;
#endif
}

//////////////////////////////////////////////////////////////////////////////
// poll() version
int
selectRWPoll(SelectObjectArray& selarray, UInt32 ms)
{
#if defined (BLOCXX_HAVE_SYS_POLL_H)
	int lerrno = 0, rc = 0;

	AutoPtrVec<pollfd> pfds(new pollfd[selarray.size()]);

	// here we spin checking for thread cancellation every so often.
	timeval now, end;
	const Int32 loopMicroSeconds = 100 * 1000; // 1/10 of a second
	gettimeofday(&now, NULL);
	end = now;
	end.tv_sec  += ms / 1000;
	end.tv_usec += (ms % 1000) * 1000;
	while ((rc == 0) && ((ms == INFINITE_TIMEOUT) || (now.tv_sec < end.tv_sec)
		 || ((now.tv_sec == end.tv_sec) && (now.tv_usec <= end.tv_usec))))
	{
		for (size_t i = 0; i < selarray.size(); i++)
		{
			BLOCXX_ASSERT(selarray[i].s >= 0);
			selarray[i].readAvailable = false;
			selarray[i].writeAvailable = false;
			selarray[i].wasError = false;
			pfds[i].revents = 0;
			pfds[i].fd = selarray[i].s;
			pfds[i].events = selarray[i].waitForRead ? (POLLIN | POLLPRI) : 0;
			if(selarray[i].waitForWrite)
				pfds[i].events |= POLLOUT;
		}

		timeval tv;
		tv.tv_sec = end.tv_sec - now.tv_sec;
		if (end.tv_usec >= now.tv_usec)
		{
			tv.tv_usec = end.tv_usec - now.tv_usec;
		}
		else
		{
			tv.tv_sec--;
			tv.tv_usec = 1000000 + end.tv_usec - now.tv_usec;
		}

		if ((tv.tv_sec != 0) || (tv.tv_usec > loopMicroSeconds) || (ms == INFINITE_TIMEOUT))
		{
			tv.tv_sec = 0;
			tv.tv_usec = loopMicroSeconds;
		}

		// TODO optimize this. 
		int loopMSecs = tv.tv_sec * 1000 + tv.tv_usec / 1000; 

		Thread::testCancel();
		rc = ::poll(pfds.get(), selarray.size(), loopMSecs); 
		lerrno = errno;
		Thread::testCancel();

		gettimeofday(&now, NULL);
	}
	
	if (rc < 0)
	{
		if (lerrno == EINTR)
		{
#ifdef BLOCXX_NETWARE
			// When the NetWare server is shutting down, select will
			// set errno to EINTR on return. If this thread does not
			// yield control (cooperative multitasking) then we end
			// up in a very tight loop and get a CPUHog server abbend.
			pthread_yield();
#endif
			return Select::SELECT_INTERRUPTED;
		}
		else
		{
			return Select::SELECT_ERROR;
		}
	}
	if (rc == 0)
	{
		return Select::SELECT_TIMEOUT;
	}
	for (size_t i = 0; i < selarray.size(); i++)
	{
		if (pfds[i].revents & (POLLERR | POLLNVAL))
		{
			selarray[i].wasError = true;
		}
		else
		{
			if(selarray[i].waitForRead)
			{
				selarray[i].readAvailable = (pfds[i].revents & 
					(POLLIN | POLLPRI | POLLHUP));
			}

			if(selarray[i].waitForWrite)
			{
				selarray[i].writeAvailable = (pfds[i].revents &
					(POLLOUT | POLLHUP));
			}
		}
	}

	return rc;
#else
	return SELECT_NOT_IMPLEMENTED;
#endif
}
//////////////////////////////////////////////////////////////////////////////
// ::select() version
int
selectRWSelect(SelectObjectArray& selarray, UInt32 ms)
{
#if defined (BLOCXX_HAVE_SYS_SELECT_H)
	int lerrno, rc = 0;
	fd_set ifds;
	fd_set ofds;

	// here we spin checking for thread cancellation every so often.
	timeval now, end;
	const Int32 loopMicroSeconds = 100 * 1000; // 1/10 of a second
	gettimeofday(&now, NULL);
	end = now;
	end.tv_sec  += ms / 1000;
	end.tv_usec += (ms % 1000) * 1000;
	while ((rc == 0) && ((ms == INFINITE_TIMEOUT) || (now.tv_sec < end.tv_sec)
		 || ((now.tv_sec == end.tv_sec) && (now.tv_usec <= end.tv_usec))))
	{
		int maxfd = 0;
		FD_ZERO(&ifds);
		FD_ZERO(&ofds);
		for (size_t i = 0; i < selarray.size(); ++i)
		{
			int fd = selarray[i].s;
			BLOCXX_ASSERT(fd >= 0);
			if (maxfd < fd)
			{
				maxfd = fd;
			}
			if (fd < 0 || fd >= FD_SETSIZE)
			{
				return Select::SELECT_ERROR;
			}
			if (selarray[i].waitForRead)
			{
				FD_SET(fd, &ifds);
			}
			if (selarray[i].waitForWrite)
			{
				FD_SET(fd, &ofds);
			}
		}

		timeval tv;
		tv.tv_sec = end.tv_sec - now.tv_sec;
		if (end.tv_usec >= now.tv_usec)
		{
			tv.tv_usec = end.tv_usec - now.tv_usec;
		}
		else
		{
			tv.tv_sec--;
			tv.tv_usec = 1000000 + end.tv_usec - now.tv_usec;
		}

		if ((tv.tv_sec != 0) || (tv.tv_usec > loopMicroSeconds) || (ms == INFINITE_TIMEOUT))
		{
			tv.tv_sec = 0;
			tv.tv_usec = loopMicroSeconds;
		}

		Thread::testCancel();
		rc = ::select(maxfd+1, &ifds, &ofds, NULL, &tv);
		lerrno = errno;
		Thread::testCancel();

		gettimeofday(&now, NULL);
	}
	
	if (rc < 0)
	{
		if (lerrno == EINTR)
		{
#ifdef BLOCXX_NETWARE
			// When the NetWare server is shutting down, select will
			// set errno to EINTR on return. If this thread does not
			// yield control (cooperative multitasking) then we end
			// up in a very tight loop and get a CPUHog server abbend.
			pthread_yield();
#endif
			return Select::SELECT_INTERRUPTED;
		}
		else
		{
			return Select::SELECT_ERROR;
		}
	}
	if (rc == 0)
	{
		return Select::SELECT_TIMEOUT;
	}
	int availableCount = 0;
	int cval;
	for (size_t i = 0; i < selarray.size(); i++)
	{
		selarray[i].wasError = false;
		cval = 0;
		if (FD_ISSET(selarray[i].s, &ifds))
		{
			selarray[i].readAvailable = true;
			cval = 1;
		}
		else
		{
			selarray[i].readAvailable = false;
		}

		if (FD_ISSET(selarray[i].s, &ofds))
		{
			selarray[i].writeAvailable = true;
			cval = 1;
		}
		else
		{
			selarray[i].writeAvailable = false;
		}

		availableCount += cval;

	}
		
	return availableCount;
#else
	return SELECT_NOT_IMPLEMENTED;
#endif
}

int
selectRW(SelectObjectArray& selarray, UInt32 ms)
{
	int rv = selectRWEpoll(selarray, ms);
	if (rv != SELECT_NOT_IMPLEMENTED)
	{
		return rv;
	}

	rv = selectRWPoll(selarray, ms);
	if (rv != SELECT_NOT_IMPLEMENTED)
	{
		return rv;
	}

	rv = selectRWSelect(selarray, ms);
	BLOCXX_ASSERT(rv != SELECT_NOT_IMPLEMENTED);
	return rv;
}

//////////////////////////////////////////////////////////////////////////////
#endif	// #else BLOCXX_WIN32

int
select(const SelectTypeArray& selarray, UInt32 ms)
{
	SelectObjectArray soa;
	soa.reserve(selarray.size());
	for (size_t i = 0; i < selarray.size(); ++i)
	{
		SelectObject curObj(selarray[i]);
		curObj.waitForRead = true;
		soa.push_back(curObj);
	}
	int rv = selectRW(soa, ms);
	if (rv < 0)
	{
		return rv;
	}

	// find the first selected object
	for (size_t i = 0; i < soa.size(); ++i)
	{
		if (soa[i].readAvailable)
		{
			return i;
		}
	}
	return SELECT_ERROR;
}

} // end namespace Select

} // end namespace BLOCXX_NAMESPACE
