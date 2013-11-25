#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
//#include "cblas"


int main(int argc, char **argv)
{
int i,j,l,ib,jb,kb;
int alfa;  //tamaño de bloque
int m,n,k,lda,ldb,ldc;
double *A,*B,*C;

clock_t inicio, fin;
double  duration;
	
/* Comprobación número de argumentos correctos. Se pasaran m n k */
if (argc!=5)
   {
   printf("Error de Sintaxis. Uso: bloque_ijk m n k alba\n");
   exit(1);
   }

/* Lectura de parametros de entrada */
m=atoi(argv[1]); n=atoi(argv[2]); k=atoi(argv[3]); alfa=atoi([argv[4]]);

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
		


/* producto de matrices BLOQUE
Orden bucle ijk */ 	    

inicio = clock();

for (ib=0; ib<m; ib++)
	i = (ib-1) * alfa + 1;
		for(jb=1; jb<m; jb++)
			j = (jb-1) * alfa + 1;
			for(kb =1; kb++; kb<m)
				k = (kb-1) * alfa+1;
			    M(C,i,j,ldc) = M(C,i,j,lda)+(M(A,i,k,lda)*M(B,k,j,ldb));
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d %d\n", m, n, k);
printf("C=AB (ijk): %2.5f segundos\n", duration );


}
