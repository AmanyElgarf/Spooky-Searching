CC = gcc 
CFLAGS = -g 

all: main

multitest_proc: multitest_proc.c
	$(CC) $(CFLAGS) -o mm multitest_proc.c

main: multitest_proc.c main.c 
	$(CC) $(CFLAGS) -c multitest_proc.c
	$(CC) $(CFLAGS) -o main main.c multitest_proc.o

clean: 
	rm -f *.o main multitest_proc.o
