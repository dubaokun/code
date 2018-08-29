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

void CCondition::Init()
{
	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_cond, NULL);
}

void CCondition::CleanUp()
{
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&
}

/*******************************class Threads*****************************/
Threads::Threads(THREAD_PTR func)
{
	m_threadname = "";
	m_err_code = 0;
	m_thread_id = 0;   
	m_workfunc = func;
}

Threads::Threads()
{
	m_thread_name = "";
	m_err_code = 0;
	m_thread_id = 0;   
	m_workfunc = NULL;
}

Threads::~Threads(void)
{

}

bool Threads::SetFunc(THREAD_PTR func)
{
	if (NULL == func) {
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
	int nret = pthread_create(&m_thread_id, &attr,(THREAD_PTR)m_workfunc, (void*)this);
	pthread_attr_destroy(&attr);

	if (nret) {
		printf("Error creating thread : %d\n",  nret);
		return false;
	} else {
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

