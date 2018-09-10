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

// the mutex to protect the res who will 
// be shared by multi threads
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


// the mutex and cond which will be use
// by threading signal and wait
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

// the function of the thread
typedef void *(*THREAD_PTR)(void *);

// the threads parent class, subclass will be inherit from this
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

	const char* GetName()const {return m_thread_name.c_str();};
	void SetName(const char*name) {m_thread_name = name;};
	int      GetLastError(void) {return m_err_code;}
	void     SetErrcode(int errcode) {m_err_code = errcode;}
	int      GetThreadID(void) {return m_thread_id;}

	static void wait_multiple_all_object(Threads **threads, int size);
	static void* workthread(void*);

protected:
    std::string     m_thread_name;
	int             m_err_code;
	pthread_t       m_thread_id;
    THREAD_PTR      m_workfunc;
};

#endif
