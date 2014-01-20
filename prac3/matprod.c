/*
IPAAP - Práctica 3
by Iván Jiménez        
*/

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "memoryfun.h"
#include "mpi.h"



int main(int argc, char *argv[]) {
        
/***** Declaración de variables para la parte de declaración de matrices ******/
        int i,j;
        int m,n,lda,ldb,ldc;
        double *A,*B,*C;
        clock_t inicio, fin;
        double duration;

/***** Declaración de variables para la parte número de procesos del Grid ******/
        
        int np_row, np_col,mb,nb;
        
/***************Inicializamos el entorno del MPI************/
/* Comentario de Kike *
* Lo primero que se ha de poner es el Init para que todos los procesos cojan
  correctamente argc y argv */
        
        MPI_Init(&argc,&argv);
        
/*** Comprobación número de argumentos correctos. Se pasaran m n np_fil np_col */
        if (argc!=7)
         {
         printf("Error de Sintaxis. Uso: matprod m n np_fil np_col\n");
         exit(1);
         }

/*** Lectura de parametros de entrada ***/
        
        m=atoi(argv[1]); n=atoi(argv[2]); np_row=atoi(argv[3]); np_col=atoi(argv[4]); mb=atoi(argv[5]); nb=atoi(argv[6]);
    /* Comentario de Kike *
       También has de introducir el tamaño de bloque por fila y columna, esto
       es MB y NB */

/***************Inicializamos el entorno BLACS************/
        int context;
        int mytid, tids;
        int myprow, mypcol;
        
        Cblacs_pinfo(&mytid,&tids);
        Cblacs_get(-1,0,&context);
        Cblacs_gridinit(&context,"R",np_row,np_col);        
        Cblacs_gridinfo(context, &np_row, &np_col, &myprow,&mypcol);
        printf("Creo el grid\n");
        
/*** Dimensionado de las matrices cuadradas, utilizando funciones propias */

        
        lda=m; ldb=m; ldc=m;
/* Comentario de Kike *
   Fíjate que sólo el proceso 0 (si consideramos que es el que actúa como 
   maestro) ha de dimensionar e inicializar las matrices globales, por 
   lo tanto par saber esto se debe haber inicializado la malla de procesos. Por
   tanto, la parte de inicialización ha de ir antes (te lo he cambiado arriba).
   A continuación el 0 reserva espacio e inicializar las matrices*/


/***************Inicializamos el entorno de las matrices************/        
        double alpha = 1.;
        double beta = 0.;
        int info;
        int desc[9];
        int zero = 0; int one = 1;


/***************Inicializamos las colas ************/
        
        inicio = clock();        
        
        
        printf("[%d/%d] myprow: %d mypcol: %d M=%d N=%d np_row=%d np_col=%d mb=%d nb=%d\n",mytid,tids,myprow,mypcol,m,n,np_row,np_col,mb,nb);         
        
        
        /**** Si soy el proceso {0,0}, relleno las matrices ( se rellenan todas en un principio) */
        
        if ((myprow==0) && (mypcol==0)){
                
            A=dmatrix(m,n); B=dmatrix(m,n); C=dmatrix(m,n);
        /**** Relleno de las matrices con valores aleatorios. Uso de macro propia */

                //matriz A

                for(i=0;i<m;i++)
                        for(j=0;j<n;j++) {
                                M(A,i,j,lda) = double i + j;
                        }
                
                //matriz B

                for(i=0;i<m;i++)
                        for(j=0;j<n;j++){
                                M(B,i,j,ldb) = double i + j;
                        }
        
                //matriz C

                for(i=0;i<m;i++)
                        for(j=0;j<n;j++){
                                M(C,i,j,ldc) = double i + j;
                        }  
				
				/********* Imprimir Matrices **************/
				
				printf("**** Matriz A ****\n");
                
				for (i=0; i<m; i++)
					for(j=0;j<n;j++){
						printf("A[%d,%d]= %d\n",i,j,M(A,i,j,lda));
					}
				printf("**** Matriz B ****\n");
                
				for (i=0; i<m; i++)
					for(j=0;j<n;j++){
						printf("B[%d,%d]= %d\n",i,j,M(B,i,j,ldb));
					}
					printf("****Matriz C****\n");
                
				for (i=0; i<m; i++)
					for(j=0;j<n;j++){
						printf("C[%d,%d]= %d\n",i,j,M(C,i,j,ldc));
					}
        }
                
        Cblacs_exit(); //cerramos blacs
        MPI_Finalize();
        fin = clock();
        duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("grid_prod: %2.5f segundos\n", duration );
        return 0;

}
