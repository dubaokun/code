// strspn() 函数用来计算字符串 str 中连续有几个字符都属于字符串 accept，其原型为：
// size_t strspn(const char *str, const char * accept);
// strcspn() 函数用来计算字符串 str 中连续有几个字符都不属于字符串 accept，其原型为：
// int strcspn(char *str, char *accept); 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int len1, len2, len3;
	char buffer[] = "25,142,330,Smith,J,239-4123";
	len1 = strspn(buffer, "0123456789");
	len2 = strspn(buffer, ",0123456789");
	printf("%d\t%d\n", len1, len2);
	char buffer1[] = "fcb74";
	len3=strcspn(buffer1, "0123456789");
	printf("%d\n", len3);

	return 0;
}
