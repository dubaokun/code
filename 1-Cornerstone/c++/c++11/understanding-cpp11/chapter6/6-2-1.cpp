#include <stdio.h>
#include <stdarg.h>
 
double SumOfFloat(int count, ...) {
    va_list ap;
    double sum = 0;
    va_start(ap, count);            // 获得变长列表的句柄ap
    for(int i = 0; i < count; i++)
        sum += va_arg(ap, double);  // 每次获得一个参数
    va_end(ap);
    return sum;
}

int main() {
    printf("%f\n", SumOfFloat(3, 1.2f, 3.4, 5.6));  // 10.200000
}
