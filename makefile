CC=g++
CFLAGS= -o

all:
	$(CC) -L/home/mehul/project3 -Wall -o yourcode.out run.cpp -laudio -I /usr/include/x86_64-linux-gnu/openblas-pthread/ -L /usr/include/x86_64-linux-gnu/ -lopenblas

clean:
	-rm*.out