#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static int count = 0;
static int step = 100000000;

void *test_func(void *arg)
{
        int i=0;
        for(i=0;i<step;++i){
			count++;
        }
        return NULL;
}

void *test_func1(void *arg)
{
        int i=0;
        for(i=0;i<step;++i){
                __sync_fetch_and_add(&count,1);
        }
        return NULL;
}

int main(int argc, const char *argv[])
{
        pthread_t id[20];
        int i = 0;

        for(i=0;i<20;++i){
                pthread_create(&id[i],NULL,test_func1,NULL);
        }

        for(i=0;i<20;++i){
                pthread_join(id[i],NULL);
        }

        printf("%d\n",count);
        return 0;
}
