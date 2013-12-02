#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
//#include "cblas"


int main(int argc, char **argv)
{
int i,j,k,ib,jb,kb;
int alfa;  //tama de bloque
int n,lda,ldb,ldc;
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
		M(C,i,j,ldc) = rand() % 20;
		
	}
		


/* producto de matrices BLOQUE
Orden bucle ijk */ 	    

inicio = clock();
printf("estoy en blucle?");
for(ib=0; ib<n; ib++)
	for(jb=0; jb<n; jb++)
		for(kb=0; kb<n; kb++)
			for(i = (ib-1) * alfa; i< (ib+1) * alfa; i++)
				for(j = (jb-1) * alfa; j< (jb+1) * alfa; j++)
					for(k = (kb-1) * alfa; k < (kb+1) * alfa; k++) {
						M(C,i,j,ldc) = M(C,i,j,ldc)+(M(A,i,k,lda) * M(B,k,j,ldb));
						//printf("i=%d,j=%d,k=%d,ib=%d,jb=%d,kb=%d,M=%d",i,j,k,ib,jb,kb,M(C,i,j,ldc));
					}
printf("estoy en blucle?");	 	   
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d \n", n, alfa);
printf("Bloques:: C=AB (ijk): %2.5f segundos\n", duration );


}
