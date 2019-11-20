#include "multitest.h"

typedef struct
{
    int    *pList;
    int    value;
    int    start;
    int    size;
    int    thread_idx;
} search_data;

void * search_thread(void *pData)
{   int i;
    int *pRet = (int *)malloc(sizeof(int)); //pointer to index of found element
    *pRet = -1;
    search_data *pSd = ( search_data *)pData;
    
    for (i = pSd->start; i < pSd->size + pSd->start; i++) { //depending on thread #, bounds set
        if (pSd->pList[i] == pSd->value) {
            
            *pRet = i;
            break;
        }
    }
    pthread_exit((void *)pRet);
}

int search(int key, int partition_size, int max_number_per_thread){
    printf("-Thread Mode\n");
    int j;
    
    struct timespec tp1, tp2;
    int numThreads = partition_size/max_number_per_thread; //     num of threads determined by ratio between size of list and how many #s you want per list
    
    pthread_t srthreads[numThreads];
    int *pstatus[numThreads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    //search_data pSd;
    search_data *pSd = malloc(numThreads * sizeof(search_data));
    
    int result = clock_gettime(CLOCK_REALTIME, &tp1);
    
    for(j=0; j<numThreads; j++)
    {
        pSd[j].thread_idx = j;
        pSd[j].value = key;
        pSd[j].size =j == numThreads-1?partition_size - j *max_number_per_thread:max_number_per_thread;
        pSd[j].start = j * max_number_per_thread;
        pSd[j].pList = array; //S + i * MAX_NUMBERS_PER_THREAD;
        pthread_create(&srthreads[j], &attr, search_thread, (void *)&pSd[j]);
        // printf("Created thread i=%d\n", j);
    }
    
    pthread_attr_destroy(&attr);
	int num = -1;
    
    for(j=0; j<numThreads; j++)
    {
        pthread_join(srthreads[j], (void **)&pstatus[j]);
        if( *pstatus[j] > -1) {
            num = j;
			
        }
        //free (pstatus[j]);
    }

	result = clock_gettime(CLOCK_REALTIME, &tp2);
    time_t sec = (tp2.tv_sec - tp1.tv_sec);
    long microsec  =  (tp2.tv_nsec - tp1.tv_nsec)/1000;

	printf("parameters of the test: \n");
	printf("number of elements per process: %d\n", max_number_per_thread);
	printf("number of threads created: %d\n", numThreads);
	printf("Array size: %d\n", partition_size);
	printf("Found %d at index %d in thread %d\n",pSd[num].value, *pstatus[num], pSd[num].thread_idx);
	printf("time=%ld.%06ld s\n", sec, microsec);
	
    printf("Exiting thread \n\n");
	return *pstatus[num];
   // free(pSd);
    //pthread_exit(NULL);
}
