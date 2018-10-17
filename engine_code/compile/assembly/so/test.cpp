#include <stdio.h>
#include "max.h"

#include <boost/thread/thread.hpp> 
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#include <cstdio>
#include <string>
#include <signal.h>
#include <execinfo.h>

static std::string getFormatedDateTime() {
    const int len = 256;
    char buffer[len] = {};
    time_t now = time(NULL);
    struct tm timeinfo = {};
    localtime_r(&now, &timeinfo);
    strftime(buffer, len, "%Y%m%d%H%M%S", &timeinfo);
    return buffer;
}

static void print_stack_fs(int sig, FILE * output)
{
    fprintf(output, "--------------------------------------\n");

    fprintf(output, "[%s] received signal=%d\n", getFormatedDateTime().c_str(), sig);

    const size_t stack_depth = 128;
    void *array[stack_depth];
    size_t size = backtrace(array, sizeof(array) / sizeof(array[0]));
    if (size > 0 && size < stack_depth) {
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

void register_signal_handler()
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
    register_signal_handler();    
    int a = 10, b = -2, c = 100;
    printf("max among 10, -2 and 100 is %d.\n", max(a, b, c));
    return 0;
}
