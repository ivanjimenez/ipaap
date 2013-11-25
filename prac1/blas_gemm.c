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
	
/* Comprobación número de argumentos correctos. Se pasaran m n k */
if (argc!=4)
   {
   printf("Error de Sintaxis. Uso: blas_gemm m n k\n");
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
		


// Computa la operacion: C <- alfa*op(A)*op(B) + beta*C
    

inicio = clock();

cblas_degmm(CblasNoTrans,CblasNoTrans,m,n,k,1.0,A,lda,B,ldb,2.0,C,ldc);
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d\n", m, n, k);
printf("C <- alfa*op(A)*op(B) + beta*C: %2.5f segundos\n", duration );


}
