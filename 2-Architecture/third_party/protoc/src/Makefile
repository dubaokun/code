WriteProtoc:main.o helloworld.pb.o
	g++ --std=c++11 -o WriteProtoc.out main.o helloworld.pb.o -lprotobuf -lpthread 

main.o:main.cpp
	g++ --std=c++11 -g -c -o main.o main.cpp

helloworld.pb.o:helloworld.pb.cc 
	g++ --std=c++11 -g -c -o helloworld.pb.o helloworld.pb.cc

clean:
	rm WriteProtoc main.o helloworld.pb.o 
