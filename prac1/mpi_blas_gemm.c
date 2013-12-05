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
#include <time.h>
#include "memoryfun.h"
#include "mpi.h"



int main(int argc, char *argv[]) {
	
	//Declaración de variables para la parte de declaración de matrices
	int result, bloqueTam, bloqueIni;
	int i,j,l;
	int m,n,k,lda,ldb,ldc;
	double *A,*B,*C;
	

	//Declaración de variables para la parte del MPI
	MPI_Status st;
 	int np, mid;
	int num, res, my_res = 0;
	
	
	/* Comprobación número de argumentos correctos. Se pasaran m n k */
	if (argc!=4)
	   {
	   printf("Error de Sintaxis. Uso: mpi_blas_gemm m n k\n");
	   exit(1);
	   }

	/* Lectura de parametros de entrada */
	m=atoi(argv[1]); n=atoi(argv[2]); k=atoi(argv[3]);

	/* Dimensionado de las matrices, utilizando funciones propias */
	lda=m; ldb=k; ldc=m;
	A=dmatrix(m,k); B=dmatrix(k,n); C=dmatrix(m,n);

	/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

	//matriz A

	for(i=0;i<m;i++)
		for(j=0;j<k;j++) {
			M(A,i,j,lda) = rand() % 20;
		
		}
		
	
	//matriz B

	for(i=0;i<k;i++)
		for(j=0;j<n;j++){
		
			M(B,i,j,ldb) = rand() % 20;
		
		}
		

	//matriz C
 
	for(i=0;i<m;i++)
		for(j=0;j<n;j++) {
			M(C,i,j,ldc) = rand() % 100;
		
		}
	
		//Inicializamos el entorno del MPI
	
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
    MPI_Comm_rank(MPI_COMM_WORLD,&mid);
	
	bloqueTam = ldb / np; //tamaño de bloque dividido en procesos
	
	// si no es múltiplo de np, habrá un resto, ese va a ser el primer bloque
	// y el resto estáran divididos de forma equitativa
	// si bloqueIni==0, querrá decir que encaja el número de bloques de n en np
	// si no, habrá uno distinto y el resto será igual
	
	bloqueIni = ldb % np; 
	
	
	if (mid==0)
	{
		// Enviamos a todos los procesos
		  for (i=1; i<np;i++){
			  //Enviamos la Matriz A completa
			  MPI_Send(&A,lda,MPI_DOUBLE,i, 0, MPI_COMM_WORLD,&st);
			  
			  //Enviamos la parte de Matriz B que corresponda
			  MPI_Send(&B,bloqueTam,MPI_DOUBLE,i, 0, MPI_COMM_WORLD,&st);
		  }
		  MPI_Receive(&C,ldc,MPI_DOUBLE,mid,0,MPI_COMM_WORLD,&st);
		  cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,m,n,k,1.0,A,lda,B,ldb,0.0,C,ldc);
	      
	      
	}
	else
	{
	      
		MPI_Receive(&A,lda,MPI_DOUBLE,mid,0,MPI_COMM_WORLD,&st);
		MPI_Receive(&B,bloqueTam,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&st);
		cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,m,n,k,1.0,A,lda,B,ldb,0.0,C,ldc);
		MPI_Send(&my_res,1,MPI_INT,0,0,MPI_COMM_WORLD);
		  
	}
	MPI_Finalize();
	return 0;  

}



