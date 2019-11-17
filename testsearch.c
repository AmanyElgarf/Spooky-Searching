
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

int create_list(int** ppList, int size)
{
	//function creates sequential list
	printf("generating %d numbers\n", size);
	*ppList = (int*)malloc(size * sizeof(int));
	int i = 0;
	if (*ppList) {
		for (i = 0; i < size; i++) {
			*(*ppList + i) = i + 1;
		}
		printf("%d numbers generated\n", i);
	}
	return (size);
}

void  randamize_list(int* pList, int size, int percentage)
{  	
	int i;
	int numPairs = size * percentage / 100; //randomizes passed in percent of number of pairs
	int idx1, idx2;
	int value;
	printf("randomizing %d numbers using %d pairs\n", size, numPairs);
        srand(time(NULL)); //randomizes with time that way no value is repeated
	for (i = 0; i < numPairs; i++) {
		idx1 = rand() % size;
		idx2 = rand() % size;
		value = pList[idx1];
		pList[idx1] = pList[idx2];
		pList[idx2] = value;
	}
	return;
}

int swap_items(int* pList, int size, int index)
{
	//swaps two randomly generated indexes
	int value = -1;
	int pos = rand() % size;
	value = pList[index];
	pList[index] = pList[pos];
	pList[pos] = value;
	//printf("swaped values at index %d with the value at index %d\n",index, pos);
	return (pos);
}

void destry_list(int** ppList)
{
	free(*ppList);
	*ppList = NULL;
	return;
}

typedef struct
{
//	variable for each thread
    int    *pList;
    int    value;
    int    start;
    int    size;
} search_data;


void * search(void *pData)
{   int i;
    int *pRet = (int *)malloc(sizeof(int)); //pointer to index of found element
    *pRet = -1;
    //pointer to iterate through list
    search_data *pSd = ( search_data *)pData;
    printf("search: value=%d, start=%d, size=%d, ptr=0x%p\n", pSd->value, pSd->start, pSd->size, pSd->pList);
   
 for (i = pSd->start; i < pSd->size + pSd->start; i++) { //depending on thread #, bounds set
        if (pSd->pList[i] == pSd->value) {
            //	printf("search: foud %d at %d, tid=0x%x\n", pSd->value, i, pthread_self());
            printf("search: foud %d at %d\n", pSd->value, i);
            *pRet = i;
            break;
        }
    }
    //	return (void *)pRet;
    pthread_exit((void *)pRet);
}


#define MAX_NUMBERS   20000
#define MAX_NUMBERS_PER_THREAD  2000
#define MAX_THREADS   80
int main()
{
    int i;
	int* pList = NULL;
	int size = MAX_NUMBERS;
	//	size of list 
	struct timespec tp1, tp2;
	int listsize = create_list(&pList, size);
	if ((pList) && (listsize == size)) {
		randamize_list(pList, size, 75);
        pthread_t srthreads[MAX_THREADS];
        int *pstatus[MAX_THREADS];
        int numThreads = MAX_NUMBERS/MAX_NUMBERS_PER_THREAD; //	 num of threads determined by ratio between size of list and how many #s you want per list
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        //search_data pSd;
        search_data *pSd = malloc(numThreads * sizeof(search_data));
      
	int result = clock_gettime(CLOCK_REALTIME, &tp1);
        
	for(i=0; i<numThreads; i++)
        {
            pSd[i].value = 276;
            pSd[i].size = MAX_NUMBERS_PER_THREAD;
            pSd[i].start = i * MAX_NUMBERS_PER_THREAD;
            pSd[i].pList = pList; //S + i * MAX_NUMBERS_PER_THREAD;
            pthread_create(&srthreads[i], &attr, search, (void *)&pSd[i]);
            printf("Created thread i=%d\n", i);
        }
        
        pthread_attr_destroy(&attr);
        
        for(i=0; i<numThreads; i++)
        {
            pthread_join(srthreads[i], (void **)&pstatus[i]);
            if( *pstatus[i] > -1) {
                result = clock_gettime(CLOCK_REALTIME, &tp2);
                time_t sec = (tp2.tv_sec - tp1.tv_sec);
                long microsec  =  (tp2.tv_nsec - tp1.tv_nsec)/1000;
                printf("Found %d at index %d, time=%ld.%06ld s\n",pSd[i].value, *pstatus[i], sec, microsec);
            }
            free (pstatus[i]);
        }
        printf("Exiting thread \n");
        free(pSd);
        destry_list(&pList);
        pthread_exit(NULL);
    }
    return 0;
}




