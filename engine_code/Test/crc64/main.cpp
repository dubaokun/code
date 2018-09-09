#include "crc64.h"
#include <string>


int test(const std::string& str)
{
	int len = str.size();
	uint64_t str_crc = 0;
	crc64(str.c_str(), len, &str_crc);	
	
	std::cout << "string=" << str << " |crc=" << str_crc << std::endl;
}

int main(int argc, char ** argv)
{
	std::string str = "profile.main.0_0";
	test(str);
	str = "0_profile.main.0";
	test(str);
	return 0;
}
