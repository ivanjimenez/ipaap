#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "memoryfun.h"
#include "cblas.h" 


int main(int argc, char **argv)
{
	
    double  m[10],n[10];
          int i;
          int result;

          printf("Enter the elements into first vector.\n");
          for(i=0;i<10;i++)
          scanf("%lf",&m[i]);

          printf("Enter the elements into second vector.\n");
          for(i=0;i<10;i++)
          scanf("%lf",&n[i]);

          result = ddot(m,n);
          printf("The result is %d\n",result);

          return 0;


}

