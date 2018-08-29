CPPFLAGS = -DENABLE_BINRELOC -pthread -W -g -D_UNIX -D_REENTRANT $(INCLUDES) 
LDFLAGS = -pthread -g
LDSOFLAGS = -shared -Wl,-soname

#CPPFLAGS = -static -pthread -D__cplusplus -D_UNIX -D_LINUX_STATIC -D_REENTRANT $(INCLUDES)
#LDFLAGS = -static -pthread 

LD = g++
TAR = peercast-linux.tgz
CC = gcc
AR = ar

INCLUDES = -I ./

LIBDIR = ../lib
libs = $(LIBDIR)/libcrawllib.so.0
		
TARGET = testthreadpool
CORE = ./

LIBSONAME = libthread.so
LIBOBJSHARED = libthread.so.0
LIBOBJSTATIC = libthread.a

CORESOURCE = ./thread.cpp \
	 ./threadPool.cpp
	


COREOBJ = $(CORESOURCE:.cpp=.o)

COREOBJSTATIC = $(CORESOURCE:.cpp=.a)
LINUXSOURCE = main.cpp 
LINUXOBJ =$(LINUXSOURCE:.cpp=.o)

# Here follow the generic build rules.
all:  $(TARGET)
	

clean:
	rm  -f $(LINUXOBJ) $(COREOBJ) $(TARGET) ${LIBOBJSTATIC} ${LIBOBJSHARED} $(COREOBJSTATIC)

%.o: %.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS) -fPIC -c $< -o $@

%.a: %.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS) -c $< -o $@

DEPENDFILE = makedepend


depend: 
	echo > $(DEPENDFILE)
	$(CC) $(INCLUDES) $(CPPFLAGS) -MD $(CORESOURCE) $(LINUXSOURCE) >> $(DEPENDFILE)

thread-so: $(COREOBJSTATIC) $(COREOBJ)
	$(LD) $(LDSOFLAGS),$(LIBSONAME) -o ${LIBOBJSHARED}  $(COREOBJ) -lc
		

$(TARGET): $(COREOBJ) $(LINUXOBJ)
	$(LD) $(LDFLAGS) -o $@  $(LINUXOBJ)  $(COREOBJ)	



