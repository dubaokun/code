#include<stdio.h>
int sum(int x, int y)
{
     int accum = 0; 
     int t;
     t = x + y;
     accum += t;
     return accum;
}
int main( int argc, char **argv)
{
       int x = 1, y = 2;
       int result = sum( x, y );
       printf("\n\n     result = %d \n\n", result);
       return 0;
}
