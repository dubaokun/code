#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define TEST_DATA_LENGTH 100000					//每个线程操作次数
#define THREAD_NUM 10							//线程个数

using namespace std;							//引入std命名空间

mutex m;										//声明互斥锁

long n_total = 0;
pthread_mutex_t g_mutex;
long p_total = 0;
long m_total = 0;
pthread_spinlock_t g_spinlock;
long s_total = 0;
atomic<long> a_total(0);						//原子量的初始化

// 在不采用互斥锁和原子类的情况下
void test_f_normal() {
    for(int i = 0; i < TEST_DATA_LENGTH; i++)
    {
        n_total += 1;
    }
}

// 使用pthread mutex互斥锁
void test_f_pthread_mutex() {
    for(int i = 0; i < TEST_DATA_LENGTH; i++)
    {
		pthread_mutex_lock(&g_mutex);
        p_total += 1;
		pthread_mutex_unlock(&g_mutex);
    }
}

// 使用c++11 mutex互斥锁
void test_f_11_mutex() {
    for(int i = 0; i < TEST_DATA_LENGTH; i++)
    {
        m.lock();
        m_total += 1;
        m.unlock();
    }
}

// 使用spin互斥锁
void test_f_spin() {
    for(int i = 0; i < TEST_DATA_LENGTH; i++)
    {
		pthread_spin_lock(&g_spinlock);
        s_total += 1;
		pthread_spin_unlock(&g_spinlock);
    }
}

// 使用原子操作
void test_f_atomic() {
    for(int i = 0; i < TEST_DATA_LENGTH; i++)
    {
        a_total += 1;
    }
}

long clock() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 * tv.tv_usec / 1000;	
	//return tv.tv_sec;
}


int main(int argc, char ** argv)
{
	pthread_mutex_init(&g_mutex, NULL);
	pthread_spin_init(&g_spinlock, 0);
    thread ts[THREAD_NUM];
    //normal mode ,result is error
    clock_t start = clock();

	/******************* use no lock ****************/
    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i] = thread(&test_f_normal);
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i].join();
    }

    clock_t end = clock();
    cout << "total: " << n_total << endl;
    cout << "test_f_normal: " << end - start << endl;

    /******************use metux*********************/
    clock_t pstart = clock();

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i] = thread(&test_f_pthread_mutex);
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i].join();
    }

    clock_t pend = clock();
    cout << "total: " << p_total << endl;
    cout << "test_f_pthread_mutex: " << pend - pstart << endl;


    /******************use metux*********************/
    clock_t mstart = clock();

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i] = thread(&test_f_11_mutex);
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i].join();
    }

    clock_t mend = clock();
    cout << "total: " << m_total << endl;
    cout << "test_f_11_mutex: " << mend - mstart << endl;

	/******************use spinlock*******************/
    clock_t sstart = clock();

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i] = thread(&test_f_spin);
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i].join();
    }

    clock_t send = clock();
    cout << "total: " << s_total << endl;
    cout << "test_f_spin: " << send - sstart << endl;


    /*****************use atomic************************/
    clock_t astart = clock();

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i] = thread(&test_f_atomic);
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        ts[i].join();
    }

    clock_t aend = clock();
    cout << "total: " << a_total << endl;
    cout << "test_f_atomic: " << aend - astart << endl;

	pthread_spin_destroy(&g_spinlock);	
	pthread_mutex_destroy(&g_mutex);
    system("pause");
    return 0;
}
