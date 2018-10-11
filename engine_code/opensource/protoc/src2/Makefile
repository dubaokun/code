ReadProtoc:main.o helloworld.pb.o
	g++ -o ReadProtoc main.o helloworld.pb.o -lprotobuf 

main.o:main.cpp
	g++ -g -c -o main.o main.cpp

helloworld.pb.o:helloworld.pb.cc 
	g++ -g -c -o helloworld.pb.o helloworld.pb.cc

clean:
	rm ReadProtoc main.o helloworld.pb.o 
