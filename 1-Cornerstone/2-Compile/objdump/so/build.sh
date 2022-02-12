g++ -g -fPIC -shared -o libmax.so max.cpp
g++ -g test.cpp -L. -lmax -Wl,-rpath=./
