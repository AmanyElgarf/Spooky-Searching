CC = gcc 

LIBS = -lm -pthread

all: 
		$(error "make to target 'proc' or 'thread'")

proc: multitest_proc.o searchtest.c
	$(CC)  searchtest.c multitest_proc.o $(LIBS)
	
multitest_proc.o: multitest_proc.c
	$(CC) -c multitest_proc.c


thread: multitest_thread.o searchtest.c
	$(CC)  searchtest.c multitest_thread.o $(LIBS)
	
multitest_thread.o: multitest_thread.c
	$(CC) -c multitest_thread.c

clean: 
	rm *.o a.out 
