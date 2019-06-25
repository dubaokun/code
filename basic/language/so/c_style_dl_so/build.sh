
g++  -shared  -fPIC  -o testso.so testso.cpp
g++ main.cpp -o main -ldl
