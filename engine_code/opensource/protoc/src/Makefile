WriteProtoc:main.o helloworld.pb.o
	g++ -o WriteProtoc.out main.o helloworld.pb.o -lprotobuf 

main.o:main.cpp
	g++ -g -c -o main.o main.cpp

helloworld.pb.o:helloworld.pb.cc 
	g++ -g -c -o helloworld.pb.o helloworld.pb.cc

clean:
	rm WriteProtoc main.o helloworld.pb.o 
