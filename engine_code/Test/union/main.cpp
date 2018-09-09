#include <iostream>

#pragma pack(1)

union ProfileStringOffset
{
	long int_value : 48;
	char str_value[6]; //存储实际字符串(长度不超过6)
};

#pragma pack()

int main(int argc, char ** argv)
{
	std::cout << sizeof(ProfileStringOffset) << std::endl;
}
