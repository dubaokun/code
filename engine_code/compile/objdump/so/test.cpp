#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <execinfo.h>
#include "max.h"

static void print_stack_fs(int sig, FILE * output)
{
    fprintf(output, "--------------------------------------\n");

	char pTime[256];
	//getSafeNow(pTime, 256);
    fprintf(output, "[%s] received signal=%d, thread_id=%ld\n",
		   	"now", sig, getpid());

    void *array[128]; // 128 stacks at most
    size_t size = backtrace(array, sizeof(array) / sizeof(array[0]));
    if (size > 0 && size < 128) {
        char ** stackLog = backtrace_symbols(array, size);
        if(stackLog) {
            for (size_t i = 0; i < size; i++) {
                fprintf(output,"%s\n", stackLog[i]);
            }
            fflush(output);
            free(stackLog);
        }
    }
}

static void sig_handler(int signo)
{
	if (signo == SIGSEGV ||
        signo == SIGBUS  ||
        signo == SIGABRT ||
        signo == SIGFPE) {

        print_stack_fs(signo, stderr);

		exit(-1);
	}
	else if (signo == SIGTERM || signo == SIGINT) {
		exit(-1);
    }
}

static void sig_register()
{
    struct sigaction sigac;
    sigemptyset(&sigac.sa_mask);
    sigac.sa_handler = sig_handler;
    sigac.sa_flags = 0;

    sigaction(SIGTERM, &sigac, 0);
    sigaction(SIGINT , &sigac, 0);
    sigaction(SIGQUIT, &sigac, 0);
    sigaction(SIGPIPE, &sigac, 0);
    sigaction(SIGBUS , &sigac, 0);
    sigaction(SIGABRT, &sigac, 0);
    sigaction(SIGFPE , &sigac, 0);
    sigaction(SIGSEGV, &sigac, 0);
}



int main(int argc, char *argv[])
{
sig_register();
    int a = 10, b = -2, c = 100;
    char * pstr = 0x00;
    int d = 100;
    *pstr = 0x00;
    printf("max among 10, -2 and 100 is %d.\n", max(a, b, c));
    return 0;
}
