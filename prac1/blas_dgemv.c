#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
#include "cblas.h" 


int main(int argc, char **argv)
{
	
	int result;
	int i,j,l;
	int m,n,lda,ldx,ldy;
	double *A,*X,*Y;
	

	clock_t inicio, fin;
	double  duration;
	
/* Comprobación número de argumentos correctos. Se pasaran m n k */

if (argc!=3)
   {
   printf("Error de Sintaxis. Uso: blas_dgemv m n\n");
   exit(1);
   }

/* Lectura de parametros de entrada */
   m=atoi(argv[1]); n=atoi(argv[2]); 
   
/* Dimensionado de las matrices, utilizando funciones propias */
   lda=m; ldx=n; ldy=n;
   A=dmatrix(m,m); X=dmatrix(1,n); Y=dmatrix(1,n);


/* Relleno de las matrices con valores aleatorios. Uso de macro propia */
   
   //Matriz A

   for (i=0;i<m;i++)
	   for(j=0;i<m;j++)
		   M(A,i,j,lda) = rand() % 20;

	//Vector X
   
   for (i=0;i<1;i++)
	   for(j=0;i<n;j++)
		   M(X,i,j,ldx) = rand() % 20;  
    
   //Vector Y
   
   for (i=0;i<1;i++)
	   for(j=0;i<n;j++)
		   M(Y,i,j,ldy) = rand() % 20;

// Computa la operaciÃ³n: cblas.dgemmv; y <- alfa*op(A)*x + beta*y
    

inicio = clock();

cblas_dgemv(CblasRowMajor,CblasNoTrans,m,n,1.0,A,m,X,1,0.0,Y,1);
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d\n", m, n);
printf("alfa*op(A)*V + beta*Y: %2.5f segundos\n", duration );


}
