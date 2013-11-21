#include <stdio.h>
#include <stdlib.h>

int main () {
	
	int i,j,k,P;
	
	int A[2][2];
	
	int B[2][2];
					 
	int C[2][2];
	
	//Valores para matriz A
	
	for (i=0;i<2;i++)
		for(j=0;j<2;j++)
			A[i][j] = rand();
	
	//Valores para matriz B
	
	for (i=0;i<2;i++)
		for(j=0;j<2;j++)
			B[i][j] = rand();
	
	//Valores para matriz C
	
	for (i=0;i<2;i++)
		for(j=0;j<2;j++)
			C[i][j] = rand();
	
	for (j=0; j<2; j++)
		for(k=0; k<2; k++)
			for(i=0; i<2; i++)
				C[i][j] = C[i][j]+(A[i][k]*B[k][j]);
				
	//Imprimir Matriz C
	
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			printf("C[%d][%d]=%d ",i,j,C[i][j]);
					 
}