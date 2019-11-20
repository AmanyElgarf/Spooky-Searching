#include "multitest.h"

void number_generator(size){
    array = (int *) malloc(size * sizeof(int));
    int i;
    for(i=0; i<size; ++i){
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

void swap(int x, int array_size){
	int y = rand()% (array_size);
    int holder = array[x];
    array[x] = array[y];
    array[y] = holder;
}

void test1(){
	number_generator(20000);
	shuffle(10);
	printf("Test(1) a\n");
	search_all(3, 10, 10);
	shuffle(50);
	printf("Test(1) b\n");
	search_all(3, 50, 50);
	shuffle(250);
	printf("Test(1) c\n");
	search_all(3, 250, 250);
	shuffle(500);
	printf("Test(1) d\n");
	search_all(3, 500, 500);
	shuffle(1000);
	printf("Test(1) e\n");
	search_all(3, 1000, 1000);
	shuffle(5000);
	printf("Test(1) f\n");
	search_all(3, 5000, 5000);
	shuffle(10000);
	printf("Test(1) g\n");
	search_all(3, 10000, 10000);
	shuffle(20000);
	printf("Test(1) h\n");
	search_all(3, 20000, 20000);
	free(array);
	printf("\n");
}

void test2(){
	int x;
	number_generator(20000);
	shuffle(250); //shufflw an array of length 250
	printf("Test(2) a\n");
	x = search_all(4, 250, 25);
	swap(x, 250);
	printf("Test(2) b\n");
	x = search_all(4, 250, 10);
	swap(x, 250);
	printf("Test(2) c\n");
	search_all(4, 250, 5);
	printf("\n");
}

void test3(){
	int x;
	shuffle(5000); //shufflw an array of length 250
	printf("Test(3) a\n");
	x = search_all(4, 5000, 1000);
	swap(x, 5000);
	printf("Test(3) b\n");
	x = search_all(4, 5000, 500);
	swap(x, 5000);
	printf("Test(3) c\n");
	x = search_all(4, 5000, 250);
	swap(x, 5000);
	printf("Test(3) d\n");
	search_all(4, 5000, 10);
	printf("\n");
}

void test4(){
	int x;
	//shuffle(10000); //shufflw an array of length 250
	printf("Test(4) a\n");
	x = search_all(98, 10000, 2000);
	swap(x, 5000);
	printf("Test(4) b\n");
	x = search_all(98, 10000, 1000);
	swap(x, 5000);
	printf("Test(4) c\n");
	x = search_all(98, 10000, 500);
	swap(x, 5000);
	printf("Test(4) d\n");
	x = search_all(98, 10000, 250);
	swap(x, 5000);
	printf("Test(4) e\n");
	x = search_all(98, 10000, 100);
	printf("\n");
}


void test5(){
	int x;
	//shuffle(20000); //shufflw an array of length 250
	printf("Test(5) a\n");
	x = search_all(87, 20000, 5000);
	swap(x, 5000);
	printf("Test(5) b\n");
	x = search_all(87, 20000, 2000);
	swap(x, 5000);
	printf("Test(5) c\n");
	x = search_all(87, 20000, 1000);
	swap(x, 5000);
	printf("Test(5) d\n");
	x = search_all(87, 20000, 500);
	swap(x, 5000);
	printf("Test(5) e\n");
	x = search_all(87, 20000, 100);
	free(array);
	printf("\n");
}

int main()
{
   
    
    //number_gennerator(); //generate the big array of size 20000
    
    
    
    ////printing the array -->delete later
   // int i; //counter
   // for(i=0; i<array_size; ++i){
    //    printf("%d   %d\n", i, array[i]);
   // }
    ////////
    
    
    test1(); //run test(1)

	test2(); //run test(2)
	test3(); //run test(3)
	test4(); //run test(4)
	test5(); //run test(5)
    
   // free(array); //free the spaces allocated to the big array
    
    return 0;
}


