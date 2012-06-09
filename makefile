CC = g++
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = antsim.o

all: antsim

antsim: $(OBJS)

antsim.o: antsim.cpp antsim.h
	$(CC) $(CFLAGS) -c antsim.cpp

clean:
	rm -f *~ *.o antsim
