#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
#include "cblas.h" 


int main(int argc, char **argv)
{
	
	int result;
	int i,j,l;
	int alfa, beta;
	int m,n,k,lda,ldb,ldc;
	double *A,*B,*C;
	double *V,*Y;

	clock_t inicio, fin;
	double  duration;
	
/* Comprobación número de argumentos correctos. Se pasaran m n k */
if (argc!=4)
   {
   printf("Error de Sintaxis. Uso: blas_dgemv n k\n");
   exit(1);
   }

/* Lectura de parametros de entrada */
m=atoi(argv[1]); n=atoi(argv[2]); k=atoi(argv[3]);

/* Dimensionado de las matrices, utilizando funciones propias */
lda=m; ldb=k; ldc=m;
A=dmatrix(m,k); B=dmatrix(k,n); C=dmatrix(m,n); V=dvector(m);

//Relleno de escalares

alfa = rand() % 20;
beta = rand() % 20;

/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

//Vector V

for(i=0;i<m;i++)
	V[i] = rand() % 20;

//Vector Y

for(i=0;i<m;i++)
	Y[i] = rand() % 20;

//matriz A

for(i=0;i<m;i++)
	for(j=0;j<k;j++) {
		M(A,i,j,lda) = rand() % 20;
		//printf("M(%d,%d)=%d\n", i, j,M(A,i,j,lda));	
	}
		
	
//matriz B

for(i=0;i<k;i++)
	for(j=0;j<n;j++){
		
		M(B,i,j,ldb) = rand() % 20;
		// printf("M(%d,%d)=%d\n", i, j,M(B,i,j,ldb));
	}
		

//matriz C
 
for(i=0;i<m;i++)
	for(j=0;j<n;j++) {
		M(C,i,j,ldc) = rand() % 100;
		//printf("M(%d,%d)=%d", i, j,M(C,i,j,ldc));
	}
		


// Computa la operaciÃ³n: cblas.dgemmv; y <- alfa*op(A)*x + beta*y
    

inicio = clock();

cblas_dgemv('CblasRowMajor','N',m,k,alfa,A,lda,V,1,beta,Y,1);
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d %d\n", m, n, k);
printf("alfa*op(A)*V + beta*Y: %2.5f segundos\n", duration );


}
