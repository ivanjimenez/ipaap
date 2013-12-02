ipaap
=====

#Introducción a la Programación de Arquitecturas de Altas Prestaciones

##Autor: Iván Jiménez Utiel

###Práctica 1: Programación Orientada a Bloques
###Contenidos de las Carpetas y Código Fuente###

###prac1

Contiene en su raíz todos los ficheros de la propia práctica

Makefile_blas
Makefile_mpi_blas
memoryfun.c		=> Crea los arrays y las matrices
memoryfun.h		=> Es el cargador de los arrays y matrices
mi_gemm_ijk.c   => Producto de Matrices C = A*B con el ordenamiento ijk

###CBLAS

Código fuente de la librería CBLAS

###pruebas

Archivos de pruebas que he ido realizando previo a la carga completa.

prac1_1kx1k.c			=> multiplica una raíz 1000x1000. Sin hacer_

prac1_prod-ijk.c		=> Producto de Matrices C = A*B con el ordenamiento ijk

prac1_prod-jki.c		=> Producto de Matrices C = A*B con el ordenamiento jki

prac_prod-kji.c			=> Producto de Matrices C = A*B con el ordenamiento kji

prac_pueba.c			=> Prueba inicial_

###mi_gemm.ijk.c
Código que realizar el producto de matrices básico teniendo en cuenta la ordenación de bucle ijk

###mi_gemm.jki.c
Código que realizar el producto de matrices básico teniendo en cuenta la ordenación de bucle jki

###mi_gemm.kji.c
Código que realizar el producto de matrices básico teniendo en cuenta la ordenación de bucle kji_

###bloque_ijk.c
Código que realiza el producto de matrices bloque teniendo en cuenta la ordenación ijk. 
Se pasan dos argumentos: n, dimensión de la matriz y alfa, dimensión de la matriz bloque; para la práctica pasaremos el tamaño 50x50 y 100x100 para matrices de 1000x1000_

###bloque_jki.c
Código que realiza el producto de matrices bloque teniendo en cuenta la ordenación jki. 
Se pasan dos argumentos: n, dimensión de la matriz y alfa, dimensión de la matriz bloque; para la práctica pasaremos el tamaño 50x50 y 100x100 para matrices de 1000x1000

###bloque_kji.c
Código que realiza el producto de matrices bloque teniendo en cuenta la ordenación kji. 
Se pasan dos argumentos: n, dimensión de la matriz y alfa, dimensión de la matriz bloque; para la práctica pasaremos el tamaño 50x50 y 100x100 para matrices de 1000x1000

###cblas_ddot.c
Computamos la operación cblas_dot<-X^T*Y

###cblas_degmv.c
Computamos la operación y <- alfa*op(A)*x + beta*y

###cblas_dgemm.c
Computamos la operación C <- alfa*op(A)*op*(B)+beta*C

