g++ -g -fPIC -shared -o libmax.so max.cpp
g++ test.cpp -L. -lmax -lboost_thread -Wl,-rpath=./
