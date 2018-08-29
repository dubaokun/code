#include <stdio.h>
#include "thread.h"

// class mutex
CMutex::CMutex()
{
	Init();
}
CMutex::~CMutex()
{
    CleanUp();
}

void CMutex::Init()
{
	pthread_mutex_init(&m_lock, NULL);
}

void CMutex::CleanUp()
{
	pthread_mutex_destroy(&m_lock);
}

bool CMutex::Acquire()
{
	pthread_mutex_lock(&m_lock);
	return  true;
}

bool CMutex::Release()
{
	pthread_mutex_unlock(&m_lock);
	return true;
}

// class condition
CCondition::CCondition()
{
	Init();
}

CCondition::~CCondition()
{
	Signal();
}
void CCondition::Init()
{
	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_cond, NULL);
}

void CCondition::Wait()
{
	pthread_mutex_lock(&m_mutex);
	pthread_cond_wait(&m_cond, &m_mutex);
	pthread_mutex_unlock(&m_mutex);
}

void CCondition::Signal()
{
	pthread_mutex_lock(&m_mutex);
	pthread_cond_signal(&m_cond);
	pthread_mutex_unlock(&m_mutex);
}

Threads::Threads(THREAD_PTR func)
{
	m_workfunc = func;
	m_ErrCode = 0;
	m_ThreadID = 0;   
}
Threads::Threads()
{
	m_workfunc = NULL;
	m_ErrCode = 0;
	m_ThreadID = 0;   
}

Threads::~Threads(void)
{

}

bool Threads::SetFunc(THREAD_PTR func)
{
	if (func == NULL)
	{
		return false;
	}
	m_workfunc = func;
	return true;
}

bool Threads::Start()
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	int nret = pthread_create(&m_ThreadID, &attr,(THREAD_PTR)m_workfunc, (void*)this);
	pthread_attr_destroy(&attr);

	if (nret)
	{
		printf("Error creating thread : %d\n",  nret);
		return false;
	}else
	{
		return true;
	}
}

void Threads::Join()
{
	pthread_join(m_ThreadID, NULL);
}

void Threads::Exit()
{
	pthread_exit(NULL);
}

void* Threads::workthread(void* argv)
{
	return NULL;
}

void Threads::wait_multiple_all_object(Threads **threads, int size)
{
	assert(threads != NULL);
	int arraysize = 0;
	for (int i = 0 ;i < size ; i ++)
	{
		if (threads[i] && threads[i]->GetThreadID() > 0)
		{
			arraysize++;
		}
	}

	for (int i =0 ; i < arraysize; i++)
	{
		threads[i]->Join();
	}
}

