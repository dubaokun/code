#include <time.h>
#include <stdint.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	std::cout << time(NULL)  << endl;

	std::cout << (uint32_t)(time(NULL) - 60) << endl;
	std::cout << static_cast<uint32_t>(time(NULL) - 60) << endl;
	return 0;
}

