/* Compile with: gcc samplep2.c -o samplep2 -fopenmp
 IPAAP - Prac3
 by Iván Jiménez
	 
   
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

	
/***************Inicializamos el entorno del MPI************/
	MPI_Status st;
 	int np, mid;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&mid);

/***************Inicializamos el entorno BLACS************/
	int context, row, col;
	
	Cblacs_pinfo(&mid,&np);
	Cblacs_get(-1,0,&context);
	Cblacs_gridinit(&context,"R",row,col);	
	
/***************Inicializamos el entorno de las matrices************/	
	bloqueTam = n / np - 1; //tamaño de bloque dividido en procesos
	bloqueIni = n % (np - 1); 
	
	
	inicio = clock();
	
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
		//dgemm_(CblasColMajor,CblasNoTrans,CblasNoTrans,m,n,k,1.0,A,lda,B,ldb,0.0,C,ldc);
		MPI_Send(C + bloqueTam * n * (i - 1),m * bloqueTam,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
		  
	}
	Cblacs_exit(); //cerramos blacs
	MPI_Finalize();
	fin = clock();
	duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
	printf("mpi_blas_dgemm: %2.5f segundos\n", duration );
	return 0;  

}