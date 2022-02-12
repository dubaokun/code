#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/mman.h>  
#include <sys/stat.h>  
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sys/timeb.h>

int get_random(bool brandom)
{
	if (!brandom)
		return 8192;

	//srand((unsigned)time(NULL));  

	struct timeb timeSeed;
	ftime(&timeSeed);
	srand(timeSeed.millitm);  // milli time
	//srand(timeSeed.time * 1000 + timeSeed.millitm);  // milli time

	int count = rand() % 20480;	
	if (200 >= count)
		return 8192;
	return count; 
}

bool init_file(int count)
{
	int fd_index = open("index.dat", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR); 
	if (fd_index < 0) return false;

	int fd_data = open("user.dat", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	if (fd_data < 0) return false;

	int ret = 0;
	unsigned long g_pos = 0;
	char buffer_index[512] = {0};
	char buffer_data[40960] = {0};
	for(int i = 0; i < count; ++i)
	{
		// calc sub_count 
		int sub_count = get_random(true);
		// write data into index file 
		sprintf(buffer_index, "%d|%lu|%d\n", i, g_pos, sub_count+1);	
		ret = write(fd_index, buffer_index, strlen(buffer_index));
		if (ret != (strlen(buffer_index))) throw std::runtime_error("write index error");

		// write data into data file
		memset(buffer_data, 0x00, 40960);
		int start = 0;
		int end = sub_count - 1; 
		sprintf(buffer_data + 1, "%d", i);
		for(int j = 0; j < sub_count; ++j)
		{
			if (0 != buffer_data[j])
				continue;

			if (0 == j) {
				buffer_data[j] = '#';
			}
			else if ((sub_count - 1) == j) {
				buffer_data[j] = '#';
			}
			else {
				buffer_data[j] = 'b';
			}
		}		

		ret = write(fd_data, buffer_data, sub_count);
		if (ret != sub_count) throw std::runtime_error("write data error");	
		g_pos += sub_count;
		ret = write(fd_data, "\n", 1);
		if (ret != 1) throw std::runtime_error("write data error");
		g_pos += 1;
	}

	close(fd_data);
	close(fd_index);
}

int main(int argc, char ** argv) 
{  
	if(argc < 2) return -1;
	int count = atoi(argv[1]);
	init_file(count);
	return 0;	
}  
