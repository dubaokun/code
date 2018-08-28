CXX = g++
CXXFLAGS += -std=c++11
LDFLAGS += -lpthread

all: test

test:  main.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -f *.o test

