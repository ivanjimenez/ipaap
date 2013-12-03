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
 	int np, mid, num, i;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
    MPI_Comm_rank(MPI_COMM_WORLD,&mid);
	
	printf("Soy el proceso %d de %d \n",mid,np);
	
	if (mid==0)
	{
	      printf("dame un numero= ");
	      scanf("%d",&num);
		  for (i=1; i<np; i++){
			  
			  MPI_Send(&num,1,MPI_INT,i,0,MPI_COMM_WORLD);
			  printf("Soy proceso 0 envío a %d\n",i);
		  }
	      
	      MPI_Recv(&num,1,MPI_INT, np-1, 0, MPI_COMM_WORLD,&st);
		  printf("El np-1 es: %d",np-1);
	  	  printf("El resultado es=%d\n",num);
	}
	else
	{
	      MPI_Recv(&num,1,MPI_INT,0,0,MPI_COMM_WORLD,&st);
		  num = num + 1;
	      MPI_Send(&num,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;  

}


