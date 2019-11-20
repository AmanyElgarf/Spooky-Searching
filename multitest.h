
#ifndef multitest_h
#define multitest_h
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
//#define total_size_of_array 20000


int* array;

#define search_all(x, y, z) search((int)x, (int)y, (int)z)


void * search_thread(void *pData);
int search(int key,  int partition_size, int max_number_per_thread);
int search_process(int key, int endIndex, int i, int child_array_size);

#endif 
