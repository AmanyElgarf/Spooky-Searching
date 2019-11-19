CC = gcc 
CFLAGS = -g 

all: multitest

multitest_proc: multitest_proc.c
	$(CC) $(CFLAGS) -o mm multitest_proc.c
	
multitest_thread: multitest_thread.c
	$(CC) $(CFLAGS) -o mm multitest_thread.c

multitest: multitest_proc.c multitest_thread.c multitest.c 
	$(CC) $(CFLAGS) -c multitest_proc.c
	$(CC) $(CFLAGS) -c multitest_thread.c
	$(CC) $(CFLAGS) -o multitest multitest.c multitest_proc.o multitest_thread.o

clean: 
	rm *.o multitest 
