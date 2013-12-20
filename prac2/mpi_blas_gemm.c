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
#include "cblas.h" 
#include "memoryfun.h"
#include "mpi.h"



int main(int argc, char *argv[]) {
	
	//Declaración de variables para la parte de declaración de matrices
	int bloqueTam, bloqueIni;
	int i,j;
	int m,n,k,lda,ldb,ldc;
	double *A,*B,*C;
	clock_t inicio, fin;
	double duration;
	

	//Declaración de variables para la parte del MPI
	MPI_Status st;
 	int np, mid;
	
	
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

	
		//Inicializamos el entorno del MPI
	
	inicio = clock();
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&mid);
	
	bloqueTam = n / np - 1; //tamaño de bloque dividido en procesos
	
	// si no es múltiplo de np, habrá un resto, ese va a ser el primer bloque
	// y el resto estáran divididos de forma equitativa
	// si bloqueIni==0, querrá decir que encaja el número de bloques de n en np
	// si no, habrá uno distinto y el resto será igual
	
	bloqueIni = n % (np - 1); 
	
	
	if (mid==0)
		
	{
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
		// Enviamos a todos los procesos
		  for (i=1; i<np;i++){
			  //Enviamos la Matriz A completa
			  MPI_Send(A,m*k,MPI_DOUBLE,i, 0, MPI_COMM_WORLD);
			  
			  //Enviamos la parte de Matriz B que corresponda
			  MPI_Send(B+bloqueTam * n * (i-1),k * bloqueTam,MPI_DOUBLE,i, 0, MPI_COMM_WORLD);
		    			  
		  }
		  
		  for (i=1; i<np; i++){
		  	  MPI_Recv(C+bloqueTam * n * (i-1),m * bloqueTam,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&st);
		  }
		  
	      //Imprimir Resultado Matriz 
		  for(i=0;i<m;i++)
			  for(j=0;j<n;j++)
				  printf("Matriz C(i,j): %d\n", M(C,i,j,ldc));
	      
	}
	else
	{
	      
		MPI_Recv(A,m*k,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&st);
		MPI_Recv(B + bloqueTam * n * (i - 1),k * bloqueTam,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&st);
		cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,m,n,k,1.0,A,lda,B,ldb,0.0,C,ldc);
		MPI_Send(C + bloqueTam * n * (i - 1),m *bloqueTam,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
		  
	}
	MPI_Finalize();
	fin = clock();
	duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
	printf("mpi_blas_dgemm: %2.5f segundos\n", duration );
	return 0;  

}



