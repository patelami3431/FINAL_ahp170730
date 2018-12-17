To make the executables, it requires the user to externally change the value of the environmental variable $LD_LIBRARY_PATH to the path that leads to the gsl-2.5/lib. Usually, it will be
> export LD_LIBRARY_PATH=$HOME/local/gsl-2.5/lib

Bonus Problem #2:

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

const int MAX = 10000;
int main()
{
       int i;
       int max_length=0; //to have a certain amount of numbers in a row
       printf("\n\n\t\t\tUGLY NUMBERS UPTO %d\n",MAX);
       for (i=1;i<MAX;i++)
       {
             int num = i;
             while(num%2 == 0)
             {
                 num=num/2;
             }
             while(num%3 == 0)
             {
                 num=num/3;
             }
             while(num%5 == 0)
             {
                 num=num/5;
             }
             if(num == 1)
             {
                 printf("%d,\t", i);
                 max_length++;
             }
             if ((max_length%10 == 0) && (num == 1))
             {
                  printf("\n");
             }
       }
      printf("\n\n");
      return 0;
}

