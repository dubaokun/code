#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/mman.h>  
#include <sys/stat.h>  
#include <iostream>

#pragma pack (1)

typedef struct{  
  char name[20];  
  short age;  
  float score;  
  char sex;  
}student;  

#pragma pack ()

int g_length = 0;

bool init_file(int count)
{
	int fd_index = open("index.dat", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR); 
	if (fd_index < 0) return false;

	int fd_data = open("user.dat", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	if (fd_data < 0) return false;

	bool write_index = false;
	int ifile_index = 0;
	int ifile_start = 0;
	int ifile_length = 0;
	int letter = 0;

	for(int i = 0; i < count; ++i)
	{
		letter = i % 26;
		if (0 == letter) {
			// do not write index file int the first time
			if (write_index) {
				char buffer_index[512] = {0};
				sprintf(buffer_index, "%d|%d|%d\n", ifile_index, ifile_start, ifile_length);
				write(fd_index, buffer_index, strlen(buffer_index));
			}

			// write index into data file
			char buffer[512] = {0};
			sprintf(buffer, "%d", i/26);
			write(fd_data, buffer, strlen(buffer));
			g_length += strlen(buffer);
		
			// record the index start length for the next write into index file
			ifile_index = i / 26;
			ifile_start = g_length - strlen(buffer);
			ifile_length = strlen(buffer);	
			write_index = true;
		}

		int fill = 97 + letter;
		char tmp = (char)fill;
		write(fd_data, &tmp, 1);
		g_length ++;
		ifile_length ++;
	}

	if (0 != letter) {
		char buffer_index[512] = {0};
		sprintf(buffer_index, "%d|%d|%d\n", ifile_index, ifile_start, ifile_length);
		write(fd_index, buffer_index, strlen(buffer_index));
	}

	close(fd_data);
	close(fd_index);
}

int main(int argc, char ** argv) 
{  
	if(argc < 2) return -1;
	int count = atoi(argv[1]);
	init_file(50000);
	return 0;	
}  
