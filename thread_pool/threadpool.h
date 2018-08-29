#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "thread.h"
#include <vector>

class CJob
{
public:
	virtual ~CJob(){};

};

class CJobWorker
{
public:
	virtual ~CJobWorker(){}
	virtual void DoJob(CJob*) = 0;
};

class CUThreadPool;
class CUWorkerThread : public Threads
{
public:

	CUWorkerThread(void);
	CUWorkerThread(THREAD_PTR func);
	virtual ~CUWorkerThread(void);

	CJob*	GetJob()		{ return m_Job;}
	CUThreadPool* GetThreadPool()	{ return m_ThreadPool;}

	void    Signal();
	void	Wait();	
	bool	IsEnd();
	static  void* work_thread(void*);

	void	SetJob(CJob* job){m_Job = job;}
	void	SetThreadPool(CUThreadPool* threadpool){m_ThreadPool = threadpool;}
	bool	End() {m_IsEnd = true;}

private:

	CCondition        m_JobCond;
	CUThreadPool      *m_ThreadPool;
	CJob              *m_Job;
	bool	          m_IsEnd;
};


class CUThreadPool
{
public:
	CUThreadPool(void);
	CUThreadPool(int initnum);
	virtual ~CUThreadPool(void);

private:
	unsigned int m_InitNum;  //Normal thread num;
	unsigned int m_ThreadNum;
	unsigned int m_WaitNum;
	CJobWorker * m_poolthread;
	CMutex	     m_lock;
	std::vector <CJob*>      m_JobList;
	std::vector <Threads*>   m_WaitThreadList;
	std::vector <Threads*>   m_ThreadList;
	//List	m_JobList;
	void    AddThread();

protected:
	Threads* GetIdleThread(void);

public:	
	
	virtual bool    Start(CJobWorker * para);
	void    Stop(void);	
	CJob*   GetJob();
	void    InsertJob(CJob* job);
	void    ApendJob(CJob* job);
	void    AppendToWaitList(Threads* jobthread);
	CJobWorker *GetJobWorker(){return m_poolthread;}
};

/*
class CUWorkerThread : public Threads
{
public:

	CUWorkerThread(void);
	CUWorkerThread(THREAD_PTR func);
	virtual ~CUWorkerThread(void);

	CJob*	GetJob()		{ return m_Job;}
	CUThreadPool* GetThreadPool()	{ return m_ThreadPool;}

	void    Signal();
	void	Wait();	
	bool	IsEnd();
	static  void* work_thread(void*);

	void	SetJob(CJob* job){m_Job = job;}
	void	SetThreadPool(CUThreadPool* threadpool){m_ThreadPool = threadpool;}
	bool	End() {m_IsEnd = true;}

private:

	CCondition        m_JobCond;
	CUThreadPool      *m_ThreadPool;
	CJob              *m_Job;
	bool	          m_IsEnd;
};*/

#endif
