#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, tid;

#pragma omp parallel private(nthreads, tid)
{

  /* Obtain thread number */
  tid = omp_get_thread_num();
  sleep(1);
  printf("Hello World from thread %d\n", tid);

  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  }  /* All threads join master thread */
}

