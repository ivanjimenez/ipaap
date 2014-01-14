/* Compile with: gcc samplep2.c -o samplep2 -fopenmp
 IPAAP - Prac3
 by Iván Jiménez
	 
   
*/

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

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
	
/***************Inicializamos el entorno del MPI************/
	MPI_Status st;
 	int np, mid;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&mid);

/***************Inicializamos el entorno BLACS************/
	int context;
	
	
	Cblacs_pinfo(&mid,&np);
	Cblacs_get(-1,0,&context);
	Cblacs_gridinit(&context,"R",1,1);	
	
/***************Inicializamos el entorno de las matrices************/	
	double alpha = 1.;
	double beta = 0.;
	
	bloqueTam = n / np - 1; //tamaño de bloque dividido en procesos
	bloqueIni = n % (np - 1); 

/***************Inicializamos las colas ************/
	
	inicio = clock();	
	
	int info;
	int desc[9];
	int zero = 0; int one = 1;

	int num_cols_local = numroc_ (&n, &bloqueTam, &mid, &zero, &np);
	int num_cols_local_protect = MAX (1, num_cols_local);
	int num_rows_local = numroc_ (&m, &bloqueTam, &mid, &zero, &np);
	int num_rows_local_protect = MAX (1, num_rows_local);
	

			
		// Distribuimos los datos
			  
	//Pregunta: ¿Debería haber un descinit por cada Matriz a multiplicar?
	
	          descinit_(desc,&m,&n,&bloqueTam,&bloqueTam,&zero,&zero,&context);
  
		  
	
    //Rutina multiplicación
			  
    dgemm_('N','N','N',&m,&n,&k,&alpha,&A,&lda,&B,&ldb,&beta,&C,&ldc);
	
	//Imprimir Resultado Matriz 
		  for(i=0;i<m;i++)
			  for(j=0;j<n;j++)
				  printf("Matriz C(i,j): %d\n", M(C,i,j,ldc));
	      	
		
	Cblacs_exit(); //cerramos blacs
	MPI_Finalize();
	fin = clock();
	duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
	printf("mpi_blas_dgemm: %2.5f segundos\n", duration );
	return 0;  

}