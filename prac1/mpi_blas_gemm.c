/* Compile with: gcc samplep2.c -o samplep2 -fopenmp
 Sample for Magister Thesis
 by Iván Jiménez
	 
   # Crear N procesos (N<=8)
   # El P0 se encarga de dividir la matriz B en N-1 bloques. 
   # Cada bloque: conjunto columnas consecutivas de B
   # P0 debe enviar al resto de procesos i<>0 la matriz A completa y la parte B que corresponda, utilizando las primitivas MPI
   # Cada proceso i debe realizar el producto de matrices utilizando cblas_dgemm 
   devolviendo el resultado a P0.
   # Finalmente, P0 recibe los resultados parciales y muestra la matriz C resultado


    ##Build:
	# make -f Makefile_mpi_blas mpi_blas_gemm
*/

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

const int MAX_STRING = 100;

int main(int argc, char *argv[]) {
	
	/* Proceso 0 divide en np-1 bloques matriz a*/
	
	char greeting[MAX_STRING];
	int comm_sz;
	int my_rank;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Coomm_rank(MPI_COMM_WORLD, &my_rank);
	
	if (my_rank != 0) {
		sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
	}

}


