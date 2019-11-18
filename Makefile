CC = gcc 
CFLAGS = -g 


multitest_proc: multitest_proc.c
	$(CC) $(CFLAGS) -o mm multitest_proc.c
	
multitest_thread: multitest_thread.c
	$(CC) $(CFLAGS) -o mm multitest_thread.c

main: multitest_proc.c main.c 
	$(CC) $(CFLAGS) -c multitest_proc.c
	$(CC) $(CFLAGS) -c multitest_thread.c
	$(CC) $(CFLAGS) -o main main.c multitest_proc.o multitest_thread.o

clean: 
	-rm *.o main multitest_proc.o multitest_thread.o
