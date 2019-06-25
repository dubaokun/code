#include "segment_hash.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	std::string filename1 = "profile.ext.0";
	size_t filesize1 = 64* 1024 * 10 + 1;
	//size_t filesize1 = 466686663;
	calc_file_segment(filename1, filesize1);
	cout << "=======================" << endl;	
	calc_offset_segment(filename1, 1000, 64* 1024 - 1000 + 1 + SEGMENT_SIZE);
	return 0;
}

