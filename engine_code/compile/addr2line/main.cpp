#include <stdio.h>
 
int func(int a, int b)
{
  return a / b;
}
 
int main()
{
  int x = 10;
  int y = 0;
  printf("%d / %d = %d\n", x, y, func(x, y));
  return 0;
}