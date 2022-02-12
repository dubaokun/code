#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <map>

using namespace std;
const int i=5;
__thread int var=i;								//两种方式效果一样
__thread char  * t_buffer = NULL;
__thread std::map<int, int>  *t_map = NULL;

void* worker1(void* arg);
void* worker2(void* arg);

int main(int argc, char ** argv)
{
    pthread_t pid1,pid2;
    static __thread  int temp=10;				//修饰函数内的static变量
    pthread_create(&pid1,NULL,worker1,NULL);
    pthread_create(&pid2,NULL,worker2,NULL);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    cout<<temp<<endl;//输出10
	cout << "main" << --var << endl;
    return 0;
}

void* worker1(void* arg)
{
	cout << "=============================================================" << endl;
    if (NULL == t_map) {
        t_map = new std::map<int, int>();
    }
    cout<<++var<<endl;//输出 6
	t_buffer = new char[1024 * 1024];
	for (int i = 0; i < 1024 * 1024; ++i) {
		t_buffer[i] = 'a';
        (*t_map)[i] = i;
    }

	cout << (*t_map).size() << endl;
	cout << "=============================================================" << endl;
}

void* worker2(void* arg)
{
    sleep(10);//等待线程1改变var值，验证是否影响线程2
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout<<++var<<endl;//输出6
	if (NULL == t_buffer)
	{
		t_buffer = new char [1024 * 1024];
		for (int i = 0; i < 1024 * 1024; ++i)
		{
			t_buffer[i] = 'b';
		}
		cout << t_buffer << endl;
	}
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}
