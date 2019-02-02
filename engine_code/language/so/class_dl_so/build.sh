
g++ -g -shared  -fPIC  -o testso.so testso.cpp
g++ -g main.cpp -o main.out -ldl
