#include <stdio.h>
#include <stdlib.h>

int main () {
	
	int A[2][2] = {{1,2},
				   {3,4}};
	
	int B[2][2] = {{5,6},
				   {7,8}};
					 
	int C[2][2] = {{0,0},
				   {0,0}};
			
	int i,j,k,P;
	
	for (k=0; k<2; k++)
		for(j=0; j<2; j++)
			for(i=0; i<2; i++)
				C[i][j] = C[i][j]+(A[i][k]*B[k][j]);
				
	//Imprimir Matriz C
	
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			printf("C[%d][%d]=%d ",i,j,C[i][j]);
					 
}