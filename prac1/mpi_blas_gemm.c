/* Compile with: gcc samplep2.c -o samplep2 -fopenmp
 Sample for Magister Thesis
 by Iván Jiménez
	 */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"



int main(int argc, char *argv[]) {
	
	/* Crear N procesos (N<=8)
	   El P0 se encarga de dividir la matriz B en N-1 bloques. 
	   Cada bloque: conjunto columnas consecutivas de B
	   P0 debe enviar al resto de procesos i<>0 la matriz A completa y la parte B que corresponda, utilizando las primitivas MPI
	   Cada proceso i debe realizar el producto de matrices utilizando cblas_dgemm 
	   devolviendo el resultado a P0.
	   Finalmente, P0 recibe los resultados parciales y muestra la matriz C resultado
	*/
	
	/*   Build:
		 make -f Makefile_mpi_blas mpi_blas_gemm
	*/


	/* Proceso 0 divide en np-1 bloques matriz a*/
	
	printf("This is a test");

}


