/* Compile with: gcc samplep2.c -o samplep2 -fopenmp
 Sample for Magister Thesis
 by Iván Jiménez
	 */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"



int main(int argc, char *argv[]) {
	
	int numtasks, rank, len, rc;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	
	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}
	
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(hostname, &len);
	printf("number of tasks= %d My rank= %d Running on %s\n", numtasks,rank,hostname);
	
	MPI_Finalize();
}

