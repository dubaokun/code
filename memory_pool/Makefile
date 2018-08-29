MemoryPool:main.o memory_slab.o
	g++ -o MemoryPool main.o memory_slab.o 

main.o:main.cpp
	g++ -g -c -o main.o main.cpp

memory_slab.o:memory_slab.cpp 
	g++ -g -c -o memory_slab.o memory_slab.cpp

clean:
	rm MemoryPool main.o memory_slab.o 
