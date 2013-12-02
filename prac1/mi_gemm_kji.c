#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
//#include "cblas"


int main(int argc, char **argv)
{
int i,j,l;
int m,n,k,lda,ldb,ldc;
double *A,*B,*C;

clock_t inicio, fin;
double  duration;
	
/* Comprobaci�n n�mero de argumentos correctos. Se pasaran m n k */
if (argc!=4)
   {
   printf("Error de Sintaxis. Uso: mi_gemm_kji m n k\n");
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
	for(j=0;j<k;j++)
		M(A,i,j,lda) = rand();
	
//matriz B
for(i=0;i<k;i++)
	for(j=0;j<n;j++)
		M(B,i,j,ldb) = rand();

//matriz C
for(i=0;i<m;i++)
	for(j=0;j<n;j++)
		M(C,i,j,ldc) = rand();


/* producto de matrices 
Orden bucle kji */ 	    

inicio = clock();

for (k=0; k<2; k++)
	for(j=0; j<2; j++)
		for(i=0; i<2; i++) 
			M(A,i,j,lda) = M(A,i,j,lda)+(M(A,i,k,lda)*M(B,k,j,ldb));
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d\n", m, n, k);
printf("C=AB (kji): %2.5f segundos\n", duration );


}
