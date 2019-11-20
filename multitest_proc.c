#include "multitest.h"
int search_process(int key, int endIndex, int i, int child_array_size){
    int index;
    int startIndex = i*child_array_size;  //start index of the process
    for(index = startIndex; index < endIndex; ++index){
        if(array[index] == key){
            return (index - i*child_array_size); //return the relative index of the child found by a given process
        }
    }
    return 255; //255 is returned when element is not found
}

int search(int key, int partition_size, int child_array_size){
    printf("-Process Mode\n");
	//clock_t start, end;
	//double time;
	//start = clock();
    struct timeval tp1, tp2;
	gettimeofday(&tp1, NULL);

    int result, i, no_of_children = ceil(partition_size/(double)child_array_size);
    int status = 255;
    int num = 0;
    for(i=0; i < no_of_children; ++i){
        pid_t pid = fork();
        
        if(pid ==0){ //child process
            int endIndex = (i == no_of_children-1)? partition_size: (i+1)*child_array_size;
            int index = search_process( key, endIndex, i, child_array_size);
            exit(index); //send the value of the relative index from the child to parent
        }
        else{ //parent process
            waitpid(pid, &result, 0); //parent waits on child to finish first
            unsigned char exit_code = WEXITSTATUS(result); //parent receives exit_code of the child
            if((int) exit_code !=255){
                status =exit_code;
                num = i;
            }
        }
    }
	gettimeofday(&tp2, NULL);
	float time = (float) tp2.tv_usec - tp1.tv_usec + tp2.tv_sec - tp1.tv_sec;
	
    
    if(status != 255){
		printf("parameters of the test: \n");
		printf("number of elements per process: %d\n", child_array_size);
		printf("number of processes created: %d\n", no_of_children);
		printf("Array size: %d\n", partition_size);
        printf("Found element %d at index %d in process %d\n",key, status + (num*child_array_size), num);
		printf("time=%f s\n", time);
    }
    else{
        printf("element is not in the array\n");
    }
    printf("Exiting process \n\n");
	return status+(num*child_array_size);
}

