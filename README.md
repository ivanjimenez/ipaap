ipaap
=====

Introducción a la Programación de Arquitecturas de Altas Prestaciones

Prácticas de Desarrollo

###Contenidos de las Carpetas###

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