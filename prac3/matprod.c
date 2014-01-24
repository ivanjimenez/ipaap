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
		double *Alocal, *Blocal, *Clocal;
        clock_t inicio, fin;
        double duration;

/***** Declaración de variables para la parte número de procesos del Grid ******/
        
        int np_row, np_col,mb,nb;
		int DESCL[9], DESCG[9]; // DESCL descritor de la Matriz local y DESCG de la Matriz Global
		int zero = 0;
		int one = 1;
        
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
        //printf("Creo el grid\n");
        
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
	    int n_filas_locales;
		int n_col_locales;
		int LLD_L, LLD_G;


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
                                M(A,i,j,lda) = (double)(i + j);
                        }
                
                //matriz B

                for(i=0;i<m;i++)
                        for(j=0;j<n;j++){
                                M(B,i,j,ldb) = (double)(i + j);
                        }
        
                //matriz C

                for(i=0;i<m;i++)
                        for(j=0;j<n;j++){
                                M(C,i,j,ldc) = (double)(i + j);
                        }  
				
				/********* Imprimir Matrices **************/
				
				printf("**** Matriz A ****\n");
                
				for (i=0; i<m; i++)
					for(j=0;j<n;j++){
						printf("A[%d,%d]= %f\n",i,j,M(A,i,j,lda));
					}
				printf("**** Matriz B ****\n");
                
				for (i=0; i<m; i++)
					for(j=0;j<n;j++){
						printf("B[%d,%d]= %f\n",i,j,M(B,i,j,ldb));
					}
					printf("****Matriz C****\n");
                
				for (i=0; i<m; i++)
					for(j=0;j<n;j++){
						printf("C[%d,%d]= %f\n",i,j,M(C,i,j,ldc));
					}
        }
		
		
		/** INICIALIZACIÓN DE DESCRIPTORES **/
		
		/* Filas Locales. Duda : 
		
		NUMROC(m,mb,myprow,zero, neprow):
		- m: número de filas en la matriz global
		- mb: tamaño de bloque de la fila
		- myprow: es el índice de la fila del proceso
		- zero: le pasamos 0 pq es la fila proceso sobre la que la primera fila de la matriz global es distribuida
		- np_row: número de filas en el proceso de
		*/
		
		/*
			Incializamos previamente antes de los descriptores un
			
		*/
		
		LLD_L = MAX(1,numroc_(&m, &mb, &myprow, &zero, &np_row));
		LLD_G = MAX(1,numroc_(&m, &m, &myprow, &zero, &np_row));
		
		
		/* Inicialización de los descriptores de las matrices: hago uno por cada matriz*/
		
		/* Descriptor de la matriz local : DESCL
		
		   - DESCL; 
		   - m: filas
		   - n: columnas
		   - mb: tamaño del bloque del gruid en filas
		    - LLD_G: es el máximo de la dimensión de la matriz global
 	   	   
		   Descriptor de la matriz local : DESCG
		
		   - DESCL; 
		   - m: filas
		   - n: columnas
		   - m: tamaño de filas global porque es el descriptor global
		   - n: tamaño de columnas global porque es el descriptor global
		   - LLD_G: es el máximo de la dimensión de la matriz global
		*/
		
		descinit_(DESCL, &m, &n, &mb, &nb, &zero, &zero, &context, &LLD_L, &info);
		descinit_(DESCG, &m, &n, &m, &n, &zero, &zero, &context, &LLD_G, &info);
		
		/*** Distribución de las Matrices */
		
		//descinit_(DESCB, &m, &n, &mb, &nb, &zero, &zero, &context, &LLD_B, &info);
		
		/*  Reserva de espacio */
		
		n_filas_locales = numroc_(&m,&mb,&myprow, &zero, &np_row);
		n_col_locales = numroc_(&n,&mb,&mypcol, &zero, &np_col);
		
		
		Alocal = dmatrix( n_filas_locales, n_col_locales );
		Blocal = dmatrix( n_filas_locales, n_col_locales );
		Clocal = dmatrix( n_filas_locales, n_col_locales );
		
		//pdgemr2d(m, n, A, ia, ja, DESCA, B, ib, jb, DESCB, context);
		
		/* Llamada a la prmitiva de distribución*/
	    
		// Distribuimos la matriz A en la Alocal
		pdgemr2d_(&m, &n, A, &one, &one, DESCG, Alocal, &one, &one, DESCL, &context);
		
		// Distribuimos la matriz B en la Blocal
		pdgemr2d_(&m, &n, B, &one, &one, DESCG, Blocal, &one, &one, DESCL, &context);
		
		/* Salida de Datos de las Matrices Distribuidas
		
		=> Ejemplo para la matriz 3x5 que teníamos:
		
		Salida de NUMROC: [0/4] myprow: -1191701840 mypcol: 0 filas locales: 2 col locales: 3
		Salida de NUMROC: [1/4] myprow: 0 mypcol: 1 filas locales: 2 col locales: 2
		Salida de NUMROC: [3/4] myprow: 1 mypcol: 1 filas locales: 1 col locales: 2
		Salida de NUMROC: [2/4] myprow: 1 mypcol: 0 filas locales: 1 col locales: 3
		
		*/	    
			
		printf("Salida de NUMROC: [%d/%d] myprow: %d mypcol: %d filas locales: %d col locales: %d\n",mytid,tids,myprow,mypcol, n_filas_locales, n_col_locales);        
			
			
		printf("Impresión de MATRICES LOCALES:\n");
		
		for (i=1;i<n_filas_locales;i++)
			for(j=1;j<n_col_locales;j++)
				printf("Alocal[%d,%d]= %f\n",i,j,M(A,i,j,lda));	
		
		for (i=1;i<n_filas_locales;i++)
			for(j=1;j<n_col_locales;j++)
				printf("Blocal[%d,%d]= %f\n",i,j,M(B,i,j,ldb));	
		
		/* Producto de dos matrices: C = AB */
		
		/* pdgemm_('N','N', &m, &n, &lda, &alfa, &Alocal, 1, 1, &DESCL, &Blocal, 1, 1, &DESCL, &beta, &Clocal, 1,1, &DESCL); */		
			
        Cblacs_exit(); //cerramos blacs
        MPI_Finalize();
        fin = clock();
        duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("grid_prod: %2.5f segundos\n", duration );
        return 0;

}
