/* Compile with: gcc samplep2.c -o samplep2 -fopenmp
 Sample for Magister Thesis
 by Iván Jiménez
	 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



int main(int argc, char *argv[]) {
	
	int tid;
	printf("hello world from threads:\n");
	
	#pragma omp parallel private(tid) 
	{
	tid = omp_get_thread_num();
	printf("<%d>\n",tid);
	
	}
	printf("I am secquential now\n");
	return 0;
	
}


