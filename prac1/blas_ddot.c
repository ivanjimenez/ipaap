#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
#include "cblas.h" 


int main(int argc, char **argv)
{
	
	int result;
	int i,j,l;
	int m,n,k,lda,ldb,ldc;
	double *A,*B;

	clock_t inicio, fin;
	double  duration;
	
	/* Comprobación número de argumentos correctos. Se pasaran m n k */
	if (argc!=4)
	   {
	   printf("Error de Sintaxis. Uso: blas_ddot n \n");
	   exit(1);
	   }

	/* Lectura de parametros de entrada */
	n=atoi(argv[1]);

	/* Dimensionado de las matrices, utilizando funciones propias */
	lda=n; ldb=n; 
	A=dmatrix(n,n); B=dmatrix(n,n);

	/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

	//matrixA (n x 1)
	

	for(i=0;i<n;i++)
		for(j=0;j<n;j++) 
			M(A,i,j,lda) = rand() % 20;
			
	//matrizB (1 x n)

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			M(B,i,j,ldb) = rand() % 20;
				
	
// Computa la operación: cblas.dot <- X^T*Y
    

inicio = clock();

result = cblas_ddot(n,A,1,B,n);
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d\n", m, result);
printf("x^T*y: %2.5f segundos\n", duration );


}
