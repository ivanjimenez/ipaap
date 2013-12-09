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
	
/* Comprobación número de argumentos correctos. Se pasaran m n k */
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

for (i = 0; i < n; i++) 
	for (j = 0; j<n; j++)
		M(C,i,j,ldc) = M(A,i,j,lda)+M(B,i,j,ldb);

fin = clock();					
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d\n", n, alfa);
printf("Bloques:: C=AB (jki): %2.5f segundos\n", duration );

}