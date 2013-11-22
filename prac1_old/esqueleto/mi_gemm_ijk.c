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




/* producto de matrices */ 	    
inicio = clock();




     
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d\n", m, n, k);
printf("C=AB (ijk): %2.1f segundos\n", duration );


}
