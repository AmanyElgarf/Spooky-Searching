#include "multitest.h"

//generate an array of os size size
void number_generator(size){
    array = (int *) malloc(size * sizeof(int));
    int i;
    for(i=0; i<size; ++i){
        array[i] = i;
    }
}

//shuffle 75% of the input array
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

//swap element of index x with random generated index given a specific array size
void swap(int x, int array_size){
	int y = rand()% (array_size);
    int holder = array[x];
    array[x] = array[y];
    array[y] = holder;
}

//find the min number in an array
int min(long int * array){
	int j;
	int min = array[0];
	for(j=1; j<30; ++j){
		if(min > array[j]){
			min = array[j];
		}
	}
	return min;
}

//find the mx number in an array
int max(long int * array){
	int j;
	int max = array[0];
	for(j=1; j<30; ++j){
		if(max < array[j]){
			max = array[j];
		}
	}
	return max;
}

//find the average of an array
double avg(long int * array){
	int j;
	int sum = array[0];
	for(j=1; j<30; ++j){
		sum = sum+array[j];
	}
	return sum/30.0;
}

//find the variance of an array
int variance(long int * array){
	double mean = avg(array);
	double sqDiff = 0;
	int j;
	for(j=0; j<30; ++j){
		sqDiff += (array[j] - mean) * (array[j] - mean);
	}
	return sqDiff/30;	
}

//find the standard deviationn of an array
double std(long int* array){
	return sqrt(variance(array));
}

//print the parameters of the test
void print_parameters(int num_ele_per_process_thread, int num_processes, int array_size){
	printf("-%s mode\n", mode);
	printf("parameters of the test: \n");
	printf("   -number of elements per %s : %d\n", mode, num_ele_per_process_thread);
	printf("   -number of %s created: %d\n", mode, num_processes);
	printf("   -Array size: %d\n\n", array_size);
}

//find and print the min, max, avg and std of an array and prints them to the user
void test_result(long int * timee){
	printf("Min = %ldµs, ", min(timee));
	printf("Max = %ldµs, ", max(timee));
	printf("Avg = %lfµs, ", avg(timee));
	printf("Std Dev = %lfµs\n\n", std(timee));
}

//run the search functionn for iterations annd store the time of each iteration in an array
long int* run_30_iterations(int key, int partition_size, int child_array_size){
	int j;
	long int *timee = (long int*) malloc(30 * sizeof(long int));
	for(j=0; j<30; ++j){
		printf("(iteration: %d) ", j); 
		fflush(stdout);
		struct timeval tp1, tp2, time;
		gettimeofday(&tp1, NULL);
		int index = search_all(key, partition_size, child_array_size);
		gettimeofday(&tp2, NULL);
		timee[j] = (tp2.tv_sec * 1000000 + tp2.tv_usec) - (tp1.tv_sec * 1000000 + tp1.tv_usec);
		printf(" , time=%ld microseconds\n", timee[j]);
		swap(index, partition_size);
	}
	printf("\n");
	return timee;
}


//test(1) --> time vs number of elements per process/thread
void test1a(){ //test time for one process/thread 
	printf("Test(1) a\n");
	print_parameters(5, 1, 5);
	shuffle(5);
	long int* timee = run_30_iterations(3, 5, 5);
	test_result(timee);
	free(timee);
}

void test1b(){ //test time for one process/thread 
	printf("Test(1) b\n");
	print_parameters(10, 1, 10);
	shuffle(10);
	long int* timee = run_30_iterations(6, 10, 10);
	test_result(timee);
	free(timee);
}

void test1c(){ //test time for one process/thread 
	printf("Test(1) c\n");
	print_parameters(20, 1, 20);
	shuffle(20);
	long int* timee = run_30_iterations(10, 20, 20);
	test_result(timee);
	free(timee);
}

void test1d(){ //test time for one process/thread 
	printf("Test(1) d\n");
	print_parameters(50, 1, 50);
	shuffle(50);
	long int* timee = run_30_iterations(16, 50, 50);
	test_result(timee);
	free(timee);
}

void test1e(){ //test time for one process/thread 
	printf("Test(1) e\n");
	print_parameters(70, 1, 70);
	shuffle(70);
	long int* timee = run_30_iterations(30, 70, 70);
	test_result(timee);
	free(timee);
}

void test1f(){ //test time for one process/thread 
	printf("Test(1) f\n");
	print_parameters(100, 1, 100);
	shuffle(100);
	long int* timee = run_30_iterations(60, 100, 100);
	test_result(timee);
	free(timee);
}

void test1g(){ //test time for one process/thread 
	printf("Test(1) g\n");
	print_parameters(150, 1, 150);
	shuffle(150);
	long int* timee = run_30_iterations(130, 150, 150);
	test_result(timee);
	free(timee);
}

void test1h(){ //test time for one process/thread 
	printf("Test(1) h\n");
	print_parameters(170, 1, 170);
	shuffle(170);
	long int* timee = run_30_iterations(150, 170, 170);
	test_result(timee);
	free(timee);
}

void test1i(){ //test time for one process/thread 
	printf("Test(1) i\n");
	print_parameters(200, 1, 200);
	shuffle(200);
	long int* timee = run_30_iterations(100, 200, 200);
	test_result(timee);
	free(timee);
}

void test1j(){ //test time for one process/thread 
	printf("Test(1) j\n");
	print_parameters(250, 1, 250);
	shuffle(250);
	long int* timee = run_30_iterations(210, 250, 250);
	test_result(timee);
	free(timee);
}


//TEST(2) and its varaitions are used to come up with a relationship between time and list size
void test2a(){ //test time for one process/thread 
	printf("Test(2) a\n");
	print_parameters(250,1, 250);
	shuffle(250);
	long int* timee = run_30_iterations(210, 250, 250);
	test_result(timee);
	free(timee);
}

void test2b(){ //test time for one process/thread 
	printf("Test(2) b\n");
	print_parameters(250, 2, 500);
	shuffle(500);
	long int* timee = run_30_iterations(9, 500, 250);
	test_result(timee);
	free(timee);
}

void test2c(){ //test time for one process/thread 
	printf("Test(2) c\n");
	print_parameters(250, 3, 750);
	shuffle(750);
	long int* timee = run_30_iterations(300, 750, 250);
	test_result(timee);
	free(timee);
}

void test2d(){ //test time for one process/thread 
	printf("Test(2) d\n");
	print_parameters(250, 4, 1000);
	shuffle(1000);
	long int* timee = run_30_iterations(20, 1000, 250);
	test_result(timee);
	free(timee);
}

void test2e(){ //test time for one process/thread 
	printf("Test(2) e\n");
	print_parameters(250, 5, 1250);
	shuffle(1250);
	long int* timee = run_30_iterations(170, 1250, 250);
	test_result(timee);
	free(timee);
}

void test2f(){ //test time for one process/thread 
	printf("Test(2) f\n");
	print_parameters(250, 30, 7500);
	shuffle(7500);
	long int* timee = run_30_iterations(90, 7500, 250);
	test_result(timee);
	free(timee);
}

void test2g(){ //test time for one process/thread 
	printf("Test(2) g\n");
	print_parameters(250, 50, 12500);
	shuffle(12500);
	long int* timee = run_30_iterations(380, 12500, 250);
	test_result(timee);
	free(timee);
}


void test2h(){ //test time for one process/thread 
	printf("Test(2) h\n");
	print_parameters(250, 70, 17500);
	shuffle(17500);
	long int* timee = run_30_iterations(210, 17500, 250);
	test_result(timee);
	free(timee);
}


void test2i(){ //test time for one process/thread 
	printf("Test(2) i\n");
	print_parameters(250, 100, 25000);
	shuffle(25000);
	long int* timee = run_30_iterations(1208, 25000, 250);
	test_result(timee);
	free(timee);
}

void test2j(){ //test time for one process/thread 
	printf("Test(2) j\n");
	print_parameters(250, 150, 37500);
	shuffle(37500);
	long int* timee = run_30_iterations(2310, 37500, 250);
	test_result(timee);
	free(timee);
}


//TEST(3) --> tradeoff point for processes vs threads
void test3a(){ //test time for one process/thread 
	printf("Test(3) a\n");
	print_parameters(250, 1, 250);
	shuffle(250);
	long int* timee = run_30_iterations(90, 250, 250);
	test_result(timee);
	free(timee);
}

void test3b(){ //test time for two processes/threads
	printf("Test(3) b\n");
	print_parameters(250, 2, 500);
	shuffle(500);
	long int* timee = run_30_iterations(80, 500, 250);
	test_result(timee);
	free(timee);
}

void test3c(){ //test time for three processes/threads
	printf("Test(3) c\n");
	print_parameters(250, 3, 750);
	shuffle(750);
	long int* timee = run_30_iterations(340, 750, 250);
	test_result(timee);
	free(timee);
}

void test3d(){ //test time for four processes/threads
	printf("Test(3) d\n");
	print_parameters(250, 4, 1000);
	shuffle(1000);
	long int* timee = run_30_iterations(930, 1000, 250);
	test_result(timee);
	free(timee);
}

void test3e(){ //test time for five processes/threads
	printf("Test(3) e\n");
	print_parameters(250, 5, 1250);
	shuffle(1250);
	long int* timee = run_30_iterations(1230, 1250, 250);
	test_result(timee);
	free(timee);
}

void test3f(){ //test time for six processes/threads
	printf("Test(3) f\n");
	print_parameters(250, 6, 1500);
	shuffle(1500);
	long int* timee = run_30_iterations(1230, 1500, 250);
	test_result(timee);
	free(timee);
}

void test3g(){ //test time for seven processes/threads
	printf("Test(3) g\n");
	print_parameters(250, 7, 1750);
	shuffle(1750);
	long int* timee = run_30_iterations(1230, 1750, 250);
	test_result(timee);
	free(timee);
}


void test3h(){ //test time for eight processes/threads
	printf("Test(3) h\n");
	print_parameters(250, 8, 2000);
	shuffle(2000);
	long int* timee = run_30_iterations(1230, 2000, 250);
	test_result(timee);
	free(timee);
}

void test3i(){ //test time for nine processes/threads
	printf("Test(3) i\n");
	print_parameters(250, 9, 2250);
	shuffle(2250);
	long int* timee = run_30_iterations(1230, 2250, 250);
	test_result(timee);
	free(timee);
}

void test3j(){ //test time for ten processes/threads
	printf("Test(3) j\n");
	print_parameters(250, 10, 2500);
	shuffle(2500);
	long int* timee = run_30_iterations(1230, 2500, 250);
	test_result(timee);
	free(timee);
}

void test3k(){ //test time for fiften processes/threads
	printf("Test(3) k\n");
	print_parameters(250, 15, 3750);
	shuffle(3750);
	long int* timee = run_30_iterations(1230, 3750, 250);
	test_result(timee);
	free(timee);
}

void test3l(){ //test time for twenty processes/threads
	printf("Test(3) l\n");
	print_parameters(250, 20, 5000);
	shuffle(5000);
	long int* timee = run_30_iterations(1230, 5000, 250);
	test_result(timee);
	free(timee);
}


test3m(){ //25 processes/threads
	printf("Test(3) m\n");
	print_parameters(250, 25, 6250);
	shuffle(6250);
	long int* timee = run_30_iterations(160, 6250, 250);
	test_result(timee);
	free(timee);
}

test3n(){ //30 processes/threads
	printf("Test(3) n\n");
	print_parameters(250, 30, 7500);
	shuffle(7500);
	long int* timee = run_30_iterations(1720, 7500, 250);
	test_result(timee);
	free(timee);
}

test3o(){ //35 processes/threads
	printf("Test(3) o\n");
	print_parameters(250, 35, 8750);
	shuffle(8750);
	long int* timee = run_30_iterations(127, 8750, 250);
	test_result(timee);
	free(timee);
}

test3p(){ //40 processes/threads
	printf("Test(3) p\n");
	print_parameters(250, 40, 10000);
	shuffle(10000);
	long int* timee = run_30_iterations(117, 10000, 250);
	test_result(timee);
	free(timee);
}

test3q(){ //45 processes/threads
	printf("Test(3) q\n");
	print_parameters(250, 45, 11250);
	shuffle(11250);
	long int* timee = run_30_iterations(1232, 11250, 250);
	test_result(timee);
	free(timee);
}

test3r(){ //50 processes/threads
	printf("Test(3) r\n");
	print_parameters(250, 50, 12500);
	shuffle(12500);
	long int* timee = run_30_iterations(2232, 12500, 250);
	test_result(timee);
	free(timee);
}

test3s(){ //150 processes/threads
	printf("Test(3) s\n");
	print_parameters(250, 150, 37500);
	shuffle(37500);
	long int* timee = run_30_iterations(4932, 37500, 250);
	test_result(timee);
	free(timee);
}

//TEST(4) --> trade off for parallelism

test4a(){      //1   process/thread on a 250 size array
	printf("Test(4) a\n");
	print_parameters(250, 1, 250);
	shuffle(250);
	long int* timee = run_30_iterations(1, 250, 250);
	test_result(timee);
	free(timee);
}

test4b(){ //2   process/thread on a 250 size array
	printf("Test(4) b\n");
	print_parameters(125, 2, 250);
	long int* timee = run_30_iterations(90, 250, 125);
	test_result(timee);
	free(timee);
}

test4c(){ //3   process/thread on a 250 size array
	printf("Test(4) c\n");
	print_parameters(84, 3, 250);
	long int* timee = run_30_iterations(43, 250, 84);
	test_result(timee);
	free(timee);
}


test4d(){ //5   process/thread on a 250 size array
	printf("Test(4) d\n");
	print_parameters(50, 5, 250);
	long int* timee = run_30_iterations(4, 250, 50);
	test_result(timee);
	free(timee);
}

test4e(){ //10  process/thread on a 250 size array
	printf("Test(4) e\n");
	print_parameters(25, 10, 250);
	long int* timee = run_30_iterations(7, 250, 25);
	test_result(timee);
	free(timee);
}

test4f(){ //20  process/thread on a 250 size array
	printf("Test(4) f\n");
	print_parameters(13, 20, 250);
	long int* timee = run_30_iterations(92, 250, 13);
	test_result(timee);
	free(timee);
}

test4g(){ //30  process/thread on a 250 size array
	printf("Test(4) g\n");
	print_parameters(9, 30, 250);
	long int* timee = run_30_iterations(40, 250, 9);
	test_result(timee);
	free(timee);
}

test4h(){ //40  process/thread on a 250 size array
	printf("Test(4) h\n");
	print_parameters(7, 40, 250);
	long int* timee = run_30_iterations(87, 250, 7);
	test_result(timee);
	free(timee);
}

test4i(){ //50  process/thread on a 250 size array
	printf("Test(4) i\n");
	print_parameters(5, 50, 250);
	long int* timee = run_30_iterations(187, 250, 5);
	test_result(timee);
	free(timee);
}

test4j(){ //250 process/thread on a 250 size array
	printf("Test(4) j\n");
	print_parameters(1, 250, 250);
	long int* timee = run_30_iterations(19, 250, 1);
	test_result(timee);
	free(timee);
}


int main()
{
   
   
	//Run GROUP(1) to figure out the relationship between time and number of elements per process/thread
	number_generator(250);
	test1a();  //5   elements per thread/process
	test1b();  //10  elements per thread/process
	test1c();  //20  elements per thread/process
	test1d();  //50  elements per thread/process
	test1e();  //70  elements per thread/process
	test1f();  //100 elements per thread/process
	test1g();  //150 elements per thread/process
	test1h();  //170 elements per thread/process
	test1i();  //200 elements per thread/process
	test1j();  //250 elements per thread/process
	free(array);

	//Run GROUP(2) to figure out the relationship between time and number of processes/threads with the number of elements per process/thread being constant(250 elements)
	number_generator(37500);
	test2a();  //1 processes/threads
	test2b();  //2 processes/threads
	test2c();  //3 processes/threads
	test2d();  //4 processes/threads
	test2e();  //5 processes/threads
	test2f();  //30 processes/threads
	test2g();  //50 processes/threads
	test2h();  //70 processes/threads
	test2i();  //100 processes/threads
	test2j();  //150 processes/threads
	free(array);
	
	//RUN GROUP(3) --> Tradeoff point for processes vs threads
	number_generator(37500);  
	test3a(); //1 processes/threads
	test3b(); //2 processes/threads
	test3c(); //3 processes/threads
	test3d(); //4 processes/threads
	test3e(); //5 processes/threads
	test3f(); //6 processes/threads
	test3g(); //7 processes/threads
	test3h(); //8 processes/threads
	test3i(); //9 processes/threads
	test3j(); //10 processes/threads
    test3k(); //15 processes/threads
	test3l(); //20 processes/threads
	test3m(); //25 processes/threads
	test3n(); //30 processes/threads
	test3o(); //35 processes/threads
	test3p(); //40 processes/threads
	test3q(); //45 processes/threads
	test3r(); //50 processes/threads
	test3s(); //150 processes/threads
	free(array);



	//RUN GROUP(4) --> Tradeoff point for parallelism
	number_generator(250);  
	test4a(); //1   process/thread on a 250 size array
	test4b(); //2   process/thread on a 250 size array
	test4c(); //3  process/thread on a 250 size array
	test4d(); //5  process/thread on a 250 size array
	test4e(); //10  process/thread on a 250 size array
	test4f(); //20  process/thread on a 250 size array
	test4g(); //30  process/thread on a 250 size array
	test4h(); //40  process/thread on a 250 size array
	test4i(); //50  process/thread on a 250 size array
	test4j(); //250  process/thread on a 250 size array
	free(array);
    return 0;
}


