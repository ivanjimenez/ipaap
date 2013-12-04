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
#include <string.h>
#include "mpi.h"

const int MAX_STRING = 100;

int main(int argc, char *argv[]) {
	
	/* Proceso 0 divide en np-1 bloques matriz a*/
	
	MPI_Status st;
 	int np, mid, i;
	int num, res = 0;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
    MPI_Comm_rank(MPI_COMM_WORLD,&mid);
	
	printf("Soy el proceso %d de %d \n",mid,np);
	res = res + 1;
	if (mid==0)
	{
	      printf("dame un numero= ");
	      scanf("%d",&num);
		  
		  for (i=1; i<np;i++){
			  MPI_Recv(&num,1,MPI_INT,i, 0, MPI_COMM_WORLD,&st);
			  res = num + res;
		  }
		  printf("El resultado es: %d\n",res);
	      
	      
	}
	else
	{
	     
		  MPI_Send(&num,1,MPI_INT,0,0,MPI_COMM_WORLD);
		  printf("Soy el proceso: %d\n",mid);
	}
	MPI_Finalize();
	return 0;  

}


