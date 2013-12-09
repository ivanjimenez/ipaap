#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "memoryfun.h"
//#include "cblas"


int main(int argc, char **argv)
{
int i,j,l, alfa;
int ib, jb, kb;
int m,n,k,lda,ldb,ldc;
double *A,*B,*C;

clock_t inicio, fin;
double  duration;
	
/* Comprobación número de argumentos correctos. Se pasarán m n k */
if (argc!=5)
   {
   printf("Error de Sintaxis. Uso: mi_gemm_ijk m n k\n");
   exit(1);
   }

/* Lectura de parámetros de entrada */
m=atoi(argv[1]); n=atoi(argv[2]); k=atoi(argv[3]); alfa=atoi(argv[4]);

/* Dimensionado de las matrices, utilizando funciones propias */
lda=m; ldb=k; ldc=m;
A=dmatrix(m,k); B=dmatrix(k,n); C=dmatrix(m,n);

/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

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
	


/* producto de matrices */ 	    
inicio = clock();

for (ib = 0; ib < n; ib++) 
	for (jb = 0; jb < n; jb++)
		for (kb = 0; kb < n; kb++)
			for (i = ib * alfa; i < (ib +1) * alfa; i++)
				for (j = jb * alfa; j < (jb +1) * alfa; j++)
					for (k = kb * alfa; kb < (kb +1)*alfa;k++)
						M(C,i,j,ldc) = M(C,i,j,ldc) + (M(A,i,k,lda) * M(B,k,j,ldb));


     
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d %d\n", m, n, k, alfa);
printf("C=AB (bloque_ijk): %2.1f segundos\n", duration );


}
