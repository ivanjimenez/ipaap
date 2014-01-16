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
	
/***** Declaración de variables para la parte de declaración de matrices ******/
	int i,j;
	int m,n,lda,ldb,ldc;
	double *A,*B,*C;
	clock_t inicio, fin;
	double duration;
	int np_fil, np_col;
	
/*** Comprobación número de argumentos correctos. Se pasaran m n np_fil np_col */
	if (argc!=5)
	   {
	   printf("Error de Sintaxis. Uso: matprod m n np_fil np_col\n");
	   exit(1);
	   }

	/* Lectura de parametros de entrada */
	m=atoi(argv[1]); n=atoi(argv[2]); np_fil=atoi(argv[3]); np_col=atoi(argv[4]);

	/* Dimensionado de las matrices cuadradas, utilizando funciones propias */
	lda=m; ldb=m; ldc=m;
	A=dmatrix(m,n); B=dmatrix(m,n); C=dmatrix(m,n);

/**** Relleno de las matrices con valores aleatorios. Uso de macro propia */

	//matriz A

	for(i=0;i<m;i++)
		for(j=0;j<n;j++) {
			M(A,i,j,lda) = rand() % 20;
		}
		
	//matriz B

	for(i=0;i<m;i++)
		for(j=0;j<n;j++){
			M(B,i,j,ldb) = rand() % 20;
		}
	
	//matriz C

	for(i=0;i<m;i++)
		for(j=0;j<n;j++){
			M(C,i,j,ldc) = rand() % 20;
		}
	
/***************Inicializamos el entorno del MPI************/
	
	MPI_Init(&argc,&argv);
	

/***************Inicializamos el entorno BLACS************/
	int context;
	int mytid, tid;
	
	Cblacs_pinfo(&mytid,&tid);
	Cblacs_get(-1,0,&context);
	Cblacs_gridinit(&context,"R",np_fil,np_col);	
	
/***************Inicializamos el entorno de las matrices************/	
	double alpha = 1.;
	double beta = 0.;
	int info;
	int desc[9];
	int zero = 0; int one = 1;


/***************Inicializamos las colas ************/
	
	inicio = clock();	
	
	printf("Creo el grid\n");      	
		
	Cblacs_exit(); //cerramos blacs
	MPI_Finalize();
	fin = clock();
	duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
	printf("mpi_blas_dgemm: %2.5f segundos\n", duration );
	return 0;  

}