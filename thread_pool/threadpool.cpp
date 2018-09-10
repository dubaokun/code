#include "threadpool.h"
#include <assert.h>

CUWorkerThread::CUWorkerThread(THREAD_PTR func):Threads(func)
{
	m_Job = NULL;
	m_ThreadPool = NULL;
	m_IsEnd = false;
}

CUWorkerThread::CUWorkerThread(void)
{
	m_Job = NULL;
	m_ThreadPool = NULL;
	m_IsEnd = false;
}

CUWorkerThread::~CUWorkerThread()
{

}

bool CUWorkerThread::IsEnd()
{
	return m_IsEnd;
}

// the workthread have two types: runing thread and waiting thread, 
// first SetJob then to dealwith the job
void* CUWorkerThread::work_thread(void* para)
{
	CUWorkerThread *pWorkThread = static_cast<CUWorkerThread*>(para);
	CJob *job = NULL;		
	CUThreadPool *threadpool = pWorkThread->GetThreadPool();
	while(!pWorkThread->IsEnd())
	{
		job = threadpool->GetJob();
		if (job != NULL)
		{
			pWorkThread->SetJob(job);
		}
		else
		{
			threadpool->AppendToWaitList(pWorkThread);
			pWorkThread->Wait(); 
		}

		// do something 
		job = (CJob*)pWorkThread->GetJob();
		if (job != NULL)
		{
			threadpool->GetJobWorker()->DoJob(job);
		}
	}
}

void CUWorkerThread::Wait()
{
	m_JobCond.Wait();
}

void CUWorkerThread::Signal()
{
	m_JobCond.Signal();
}

//******CUThreadPool Function******//


CUThreadPool::CUThreadPool()
{
	m_InitNum = 4 ;  
	m_ThreadNum = 0;
	m_ThreadList.clear();
	m_WaitThreadList.clear();
}

CUThreadPool::CUThreadPool(int initnum)
{
	m_InitNum = initnum ;  
	m_ThreadNum = 0;
	m_WaitThreadList.clear();
	m_ThreadList.clear();
}

CUThreadPool::~CUThreadPool()
{
	Stop();
}

bool CUThreadPool::Start(CJobWorker * pt)
{
	assert(pt != NULL);
	m_JobWorker = pt;
	for(unsigned int i=0; i<m_InitNum; i++)
	{
		AddThread();
	}
	return true;
}

void CUThreadPool::AddThread()
{
	CUWorkerThread* pWorkThread = new CUWorkerThread(CUWorkerThread::work_thread);
	assert(pWorkThread != NULL);
	pWorkThread->SetThreadPool(this);
	m_ThreadList.push_back(pWorkThread);
	m_ThreadNum++;
	pWorkThread->Start();
}

void CUThreadPool::Stop()
{	
	for(unsigned int i = 0; i < m_ThreadList.size(); i++) 
	{
		CUWorkerThread* pWorkThread =(CUWorkerThread*) m_ThreadList[i];
		pWorkThread->End();
		pWorkThread->Join();
		delete pWorkThread;
	}
	return;
}

Threads* CUThreadPool::GetIdleThread(void)
{
	if (m_WaitThreadList.size() == 0 )
	{
		return NULL;
	}
	Threads* pThread = NULL;
	std::vector<Threads*>::iterator it;		
	if(m_WaitThreadList.size() > 0 )
	{
		it = m_WaitThreadList.begin();
		pThread = *it;
		m_WaitThreadList.erase(it);		
		m_WaitNum--;
		//printf("Get Idle thread %d\n", pThread->GetThreadID());
	}

	return pThread;
}

void CUThreadPool::AppendToWaitList(Threads* jobthread)
{
	m_lock.Acquire();
	{
		m_WaitThreadList.push_back(jobthread);
		m_WaitNum++;
	}
	m_lock.Release();
}

CJob* CUThreadPool::GetJob()
{
	CJob *job = NULL;
	std::vector<CJob*>::iterator it;
	m_lock.Acquire();
	{
		if (m_JobList.size() > 0)
		{
			it = m_JobList.begin();
			job = *it;
			m_JobList.erase(it);
		}
	}
	m_lock.Release();
	return job;
}

void CUThreadPool::InsertJob(CJob* job)
{
	if (job == NULL)
		return;

	m_lock.Acquire();
	{

		CUWorkerThread*  pIdleThread = (CUWorkerThread*)GetIdleThread();

		if(pIdleThread != NULL)
		{
			pIdleThread->SetJob(job);
			pIdleThread->Signal();
			//printf("Job is set to thread %d \n", pIdleThread->GetThreadID());
		}
		else
		{
			m_JobList.insert(m_JobList.begin(), job);
		}
	}
	m_lock.Release();
}

void CUThreadPool::ApendJob(CJob* job)
{
	if (job == NULL)
		return;

	m_lock.Acquire();
	{
		CUWorkerThread*  pIdleThread = (CUWorkerThread*)GetIdleThread();

		if(pIdleThread != NULL)
		{
			m_WaitNum--;
			pIdleThread->SetJob(job);
			pIdleThread->Signal();
			//printf("Job is set to thread %d \n", pIdleThread->GetThreadID());
		}
		else
		{
			m_JobList.push_back(job);
		}
	}
	m_lock.Release();
}
