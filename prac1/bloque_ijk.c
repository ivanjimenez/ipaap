#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
//#include "cblas"


int main(int argc, char **argv)
{
int i,j,l,ib,jb,kb;
int alfa;  //tama�o de bloque
int n,k,lda,ldb,ldc;
double *A,*B,*C;

clock_t inicio, fin;
double  duration;
	
/* Comprobaci�n n�mero de argumentos correctos. Se pasaran m n k */
if (argc!=3)
   {
   printf("Error de Sintaxis. Uso: bloque_ijk n alfa\n");
   exit(1);
   }

/* Lectura de parametros de entrada */
n=atoi(argv[1]); alfa=atoi(argv[2]);

/* Dimensionado de las matrices, utilizando funciones propias */
lda=n; ldb=n; ldc=n;
A=dmatrix(n,n); B=dmatrix(n,n); C=dmatrix(n,n);

/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

//matriz A

for(i=0;i<n;i++)
	for(j=0;j<n;j++) {
		M(A,i,j,lda) = rand() % 20;
			
	}
		
	
//matriz B

for(i=0;i<n;i++)
	for(j=0;j<n;j++){
		
		M(B,i,j,ldb) = rand() % 20;
		
	}
		

//matriz C

for(i=0;i<n;i++)
	for(j=0;j<n;j++) {
		M(C,i,j,ldc) = rand() % 100;
		
	}
		


/* producto de matrices BLOQUE
Orden bucle ijk */ 	    

inicio = clock();

for (ib=0; ib<n; ib++)
	for (i = (ib-1) * alfa + 1; i==ib*alfa;i++)
		for(jb=0; jb<n; jb++)
			for(j = (jb-1) * alfa + 1;j==jb*alfa;j++)	
				for(kb=0; kb++; kb<n)
					for(k = (kb-1) * alfa+1;k==jb*alfa;k++)
			   	 	   M(C,i,j,ldc) = M(C,i,j,ldc)+(M(A,i,k,lda) * M(B,k,j,ldb));
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d \n", n, alfa);
printf("Bloques:: C=AB (ijk): %2.5f segundos\n", duration );


}
