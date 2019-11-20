#include "multitest.h"

void number_gennerator(){
    array = (int *) malloc(total_size_of_array * sizeof(int));
    int i;
    for(i=0; i<total_size_of_array; ++i){
        array[i] = i;
    }
}
void shuffle(int partition_size){
    int i;
    for(i=0; i<(partition_size*.75); ++i){
        int one = rand() % (partition_size);
        int two = rand() % (partition_size);
        int holder = array[one];
        array[one] = array[two];
        array[two] = holder;
    }
}

void swap(int x, int y){
    int holder = array[x];
    array[x] = array[y];
    array[y] = holder;
}

int main()
{
    int array_size = 1500; //the size of the sub array where we are running the search
    int max_number_per_process = 10;
    int max_number_per_thread = 10;
    int key = 440;

    
    number_gennerator();
    shuffle(array_size);
    
    
    ////printing the array -->delete later
    int i; //counter
    for(i=0; i<array_size; ++i){
        printf("%d   %d\n", i, array[i]);
    }
    ////////
    
    
    multi_process(key, array_size, max_number_per_process);
    
    multi_thread(key,  array_size,  max_number_per_thread);
    
    free(array);
    
    return 0;
}


