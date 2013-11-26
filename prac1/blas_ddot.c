#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
#include "cblas.h" 


int main(int argc, char **argv)
{
	
	int result;
	int i,j,l;
	int m,ldx,ldy;
	double *X,*Y;

	clock_t inicio, fin;
	double  duration;
	
/* Comprobación número de argumentos correctos. Se pasaran m n k */
if (argc!=2)
   {
   printf("Error de Sintaxis. Uso: blas_ddot m \n");
   exit(1);
   }

/* Lectura de parametros de entrada */
m=atoi(argv[1]); 

/* Dimensionado de las matrices, utilizando funciones propias */
ldx=m; ldy=m; 
X=dvector(m); Y=dvector(m); 

/* Relleno de vectores con valores aleatorios. Uso de macro propia */

//vector X

for(i=0;i<m;i++)
	X[i] = rand() % 20;
	
//matriz Y

for(i=0;i<m;i++)
	Y[i] = rand() % 20;		


// Computa la operación: cblas.dot <- X^T*Y
    

inicio = clock();

result = cblas_ddot(m,X,1,Y,1);
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d\n", m, result);
printf("x^T*y: %2.5f segundos\n", duration );


}
