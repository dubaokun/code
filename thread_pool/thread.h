/*
 * Brief: thread pool 
 * Author: Sam
 * Data: 2018/08/23
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <iostream>
#include <assert.h>

/************************mutex*****************************/
class CMutex
{
public:
	CMutex();
	~CMutex();

	bool Acquire();
	bool Release();

private:
	void Init();
    void CleanUp();

	pthread_mutex_t m_lock;
};


/**********************cond********************************/
class CCondition
{
public:
	CCondition();
	~CCondition();

	void Wait();
	void Signal();

private:
	void Init();
	void CleanUp();

	pthread_cond_t m_cond;
	pthread_mutex_t m_mutex;
};


typedef void *(*THREAD_PTR)(void *);

/************************thread****************************/
class  Threads
{
public:
	Threads(THREAD_PTR);
	Threads();

	virtual ~Threads();

	bool     SetFunc(THREAD_PTR func);
	bool     Start();        				//Start to execute the thread
	void     Join(void);
	void     Exit(void);

	const char* GetName()const {return m_threadname.c_str();};
	void SetName(const char*name) {m_threadname = name;};
	int      GetLastError(void) {return m_ErrCode;}
	void     SetErrcode(int errcode) {m_ErrCode = errcode;}
	int      GetThreadID(void) {return m_ThreadID;}

	static void wait_multiple_all_object(Threads **threads, int size);
	static void* workthread(void*);

protected:
    std::string     m_thread_name;
	int             m_errr_code;
	pthread_t       m_thread_id;
    THREAD_PTR      m_workfunc;
};

#endif
