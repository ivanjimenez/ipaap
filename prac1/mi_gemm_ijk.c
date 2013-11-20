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
	
/* Comprobación número de argumentos correctos. Se pasarán m n k */
if (argc!=4)
   {
   printf("Error de Sintaxis. Uso: mi_gemm_ijk m n k\n");
   exit(1);
   }

/* Lectura de parámetros de entrada */
m=atoi(argv[1]); n=atoi(argv[2]); k=atoi(argv[3]);

/* Dimensionado de las matrices, utilizando funciones propias */
lda=m; ldb=k; ldc=m;
A=dmatrix(m,k); B=dmatrix(k,n); C=dmatrix(m,n);

/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

//matriz A
for(i=0;i<m;i++)
	for(j=0;j<k;j++)
		A[i][j] = rand();
	
//matriz B
for(i=0;i<k;i++)
	for(j=0;j<n;j++)
		B[i][j] = rand();

//matriz C
for(i=0;i<m;i++)
	for(j=0;j<n;j++)
		[i][j] = rand();

/* producto de matrices */ 	    
inicio = clock();

for (i=0; i<2; i++)
	for(j=0; j<2; j++)
		for(l=0; l<2; l++)
			C[i][j] = C[i][j]+(A[i][l]*B[l][j]);


     
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d\n", m, n, k);
printf("C=AB (ijk): %2.1f segundos\n", duration );


}
