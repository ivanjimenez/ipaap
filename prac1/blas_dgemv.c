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
	double *A,*V;
	

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


/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

//Vector V

double x[] = {
 -1, -1, 1
};

//Vector Y

double y[] = {
0, 0, 0
};

//matriz A
double M[] = {
3,1,3,
1,5,9,
2,6,5
};

//matriz B
		


// Computa la operaciÃ³n: cblas.dgemmv; y <- alfa*op(A)*x + beta*y
    

inicio = clock();

cblas_dgemv(CblasRowMajor,CblasNoTrans,3,3,1.0,M,3,x,1,0.0,y,1);
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d %d\n", m, n, k);
printf("alfa*op(A)*V + beta*Y: %2.5f segundos\n", duration );


}
