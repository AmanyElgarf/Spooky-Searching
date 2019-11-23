#include "multitest.h"
const char *mode = "process";
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
    int i, no_of_children = ceil(partition_size/(double)child_array_size);
	pid_t pids[no_of_children];
    int statuss = 255;
    int num = 0;
    for(i=0; i < no_of_children; ++i){
		if((pids[i] = fork()) == 0){
			int result;
			int endIndex = (i == no_of_children-1)? partition_size: (i+1)*child_array_size;
			result = search_process( key, endIndex, i, child_array_size);
			exit(result);
		}
	}
	int status[no_of_children], result;
	for(i=0; i< no_of_children; ++i){
		waitpid(pids[i], &result, 0);
		unsigned char exit_code = WEXITSTATUS(result);
		status[i] = exit_code;
		
	}
	
	for(i=0; i<no_of_children; ++i){
		if((int) status[i] !=255){
                statuss =status[i];
                num = i;
            }
	}
	

    if(statuss != 255){
        printf("Found element %d at index %d in process %d",key, statuss + (num*child_array_size), num);
    }
    else{
        printf("element is not in the array\n");
    }

	return statuss+(num*child_array_size);
}

