CC          = mpicc

BLACSFINIT  = /home/lib/blacsF77init_MPI-LINUX-0.a
BLACSCINIT  = /home/lib/blacsCinit_MPI-LINUX-0.a
BLACSLIB    = /home/lib/blacs_MPI-LINUX-0.a
CBLACSLIB     = $(BLACSCINIT) $(BLACSLIB) $(BLACSCINIT)
FBLACSLIB     = $(BLACSFINIT) $(BLACSLIB) $(BLACSFINIT)

SCALAPACKLIB= /home/lib/libscalapack.a

BLASLIB     = /home/lib/blas_LINUX.a
LAPACKLIB   = /home/lib/lapack_LINUX.a


LIBS         = $(SCALAPACKLIB) $(FBLACSLIB) $(LAPACKLIB) $(BLASLIB) -lgfortran -lm

matprod: matprod.c 
	$(CC) -c matprod.c -o matprod.o
	$(CC) -c memoryfun.c -o memoryfun.o
	$(CC) -o matprod matprod.o memoryfun.o $(LIBS)

clean: 
	rm *.o
	rm matprod

