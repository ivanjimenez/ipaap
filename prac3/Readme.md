#### Para lanzar el programa 
- Basta con ejecutar esta orden en el shell, por ejemplo, para 8 procesos, una matriz 5x3 y un grid 2x2

$ mpiexec -n 8 ./matprod 5 3 2 2

## Salida: 

 mpiexec -n 8 ./matprod 5 3 2 2 2 2
Creo el grid
[4/8] myprow: -1 mypcol: -1 M=5 N=3 np_row=-1 np_col=-1 mb=2 nb=2
Creo el grid
Creo el grid
Creo el grid
[0/8] myprow: 0 mypcol: 0 M=5 N=3 np_row=2 np_col=2 mb=2 nb=2
Creo el grid
Creo el grid
[3/8] myprow: 1 mypcol: 1 M=5 N=3 np_row=2 np_col=2 mb=2 nb=2
[6/8] myprow: -1 mypcol: -1 M=5 N=3 np_row=-1 np_col=-1 mb=2 nb=2
Creo el grid
[2/8] myprow: 1 mypcol: 0 M=5 N=3 np_row=2 np_col=2 mb=2 nb=2
[5/8] myprow: -1 mypcol: -1 M=5 N=3 np_row=-1 np_col=-1 mb=2 nb=2
[1/8] myprow: 0 mypcol: 1 M=5 N=3 np_row=2 np_col=2 mb=2 nb=2
Creo el grid
[7/8] myprow: -1 mypcol: -1 M=5 N=3 np_row=-1 np_col=-1 mb=2 nb=2
grid_prod: 0.00000 segundos
grid_prod: 0.00000 segundos
grid_prod: 0.00000 segundos
grid_prod: 0.00000 segundos
grid_prod: 0.00000 segundos
grid_prod: 0.00000 segundos
grid_prod: 0.00000 segundos
grid_prod: 0.00000 segundos