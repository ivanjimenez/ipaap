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
	double *A,*B,*C;

	clock_t inicio, fin;
	double  duration;
	
/* Comprobación número de argumentos correctos. Se pasaran m n */
if (argc!=3)
   {
   printf("Error de Sintaxis. Uso: blas_dgemv m n\n");
   exit(1);
   }

/* Lectura de parametros de entrada */
m=atoi(argv[1]); n=atoi(argv[2]); 

/* Dimensionado de las matrices, utilizando funciones propias */
lda=m; ldb=n; ldc=n;
A=dmatrix(m,m); B=dmatrix(n,n); C=dmatrix(n,n);

/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

//matriz A

for(i=0;i<m;i++)
	for(j=0;j<m;j++) {
		M(A,i,j,lda) = rand() % 20;
		
	}
	
//matriz B


	for(j=0;j<n;j++)
		
		M(B,i,j,ldb) = rand() % 20;
		
	
		

//matriz C
 

	for(j=0;j<n;j++) 
		M(C,i,j,ldc) = rand() % 100;


// Computa la operacion: C <- alfa * op(A) * X * + beta*Y
    

inicio = clock();

for(j=0;j<n;j++)
	M(C,i,j,ldc) = cblas_dgemv(CblasRowMajor,CblasNoTrans,m,n,1.0,A,lda,B,1,0.0,C,1);
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d\n", m, n, k);
printf("C <- alfa * op(A) * X * + beta * Y: %2.5f segundos\n", duration );


}

