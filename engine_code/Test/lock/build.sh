#/bin/sh
g++ -D_GLIBCXX_USE_NANOSLEEP -g -Wall -std=c++0x dead_lock_demo.cpp -o dead_lock_demo -g -pthread
g++ -g lock.cpp -o lock -lpthread
