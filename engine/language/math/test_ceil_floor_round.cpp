/*
 * #include <math.h>
 *  
 *  double ceil(double x);
 *  double floor(double x);
 *  double round(double x);
 *
 * ceil(x)返回不小于x的最小整数值（然后转换为double型）。
 *
 * floor(x)返回不大于x的最大整数值。
 *
 * round(x)返回x的四舍五入整数值。
 */

#include <stdio.h>
#include <math.h>
 
int main(int argc, const char *argv[])
{
 
    //float num = 1.4999;
    float num = 1.4999;
 
    printf("ceil(%f) is %f\n", num, ceil(num));
 
    printf("floor(%f) is %f\n", num, floor(num));
 
    printf("round(%f) is %f\n", num, round(num));
 
    return 0;
 
}
