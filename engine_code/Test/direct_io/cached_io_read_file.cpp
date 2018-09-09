/**
 * gcc cached_io_read_file.c -o cached_io_read_file -D_GNU_SOURCE
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <string.h>
#include <iostream>
#include <stdexcept>

using namespace std;

#define BLOCK_SIZE 4096 

int str_split_ex(char *src, const char seperator,
                 char **cols, const int max_cols) 
{
    char *p;
    char **current;
    int count = 0;

    if (max_cols <= 0) {
        return 0;
    }

    p = src;
    current = cols;

    while (true) {
        *current = p;
        current++;

        count++;
        if (count >= max_cols) {
            break;
        }

        p = strchr(p, seperator);
        if (p == NULL) {
            break;
        }

        *p = '\0';
        p++;
    }

    return count;
}


int g_fd = -1;

// open the file in the cached mode
bool open_file(const char * filename)
{
	g_fd = open(filename, O_RDONLY);
	if (g_fd < 0) return false;
	return true;
}

// read file content in cached IO mode
int read_file(size_t start, int length, char * buffer)
{
	size_t data_pos_align_absolute = 0;
	int block_size = 0;
	
	//cout << "start " << start << endl;
	//cout << "length " << length << endl;
	
	int ret = pread(g_fd, buffer, length, start);
    if (ret < 0) {
		return -5;
    }
			
	return 0;
}

int main()
{
	time_t begin_time = time(NULL);
	int pagesize = getpagesize();
	std::cout << "pagesize=" << pagesize << std::endl;

	FILE * fp = fopen("./data/index.dat", "r");
	if (NULL == fp) {
		std::cout << "fopen file index.dat failed" << std::endl;
	}

	if (!open_file("./data/user.dat")) return -1;
	
	char line[512] = {0};
	int index = 1;
	while(fgets(line, 512, fp))
	{
		int len = strlen(line);
		if (len > 0 && line[len - 1] == '\n') line[--len] = 0;
		char * split_list[3];
		int split = str_split_ex(line, '|', split_list, 3);
		if(split < 3) {
			std::cout << "less line" << std::endl;
			exit(0);
		}

		size_t start = strtoul(split_list[1], NULL, 10);
		int length = strtol(split_list[2], NULL, 10);

		std::cout << index-1 << "  =============================" << std::endl;

		char buffer[40960] = {0};
		int ret = read_file(start, length, buffer);		

		//std::cout << "ret " << ret << " read size=" << strlen(buffer) << std::endl;
		//std::cout << buffer << std::endl;

		if ('#' != buffer[0]) throw std::runtime_error("head error");
		if ('#' != buffer[strlen(buffer) - 2]) throw std::runtime_error("tail #  error");
		if ('\n' != buffer[strlen(buffer) - 1]) throw std::runtime_error("tail n error");
		for (int i = (1 + index); i < strlen(buffer) - 2; ++i) {
			if ('b' != buffer[i])
				throw std::runtime_error("content error");
		}
		++ index;
	}

	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	time_t end_time = time(NULL);
	std::cout << "Use time=" << end_time - begin_time << std::endl;
	while(1)
		sleep(10);
	fclose(fp);
    close(g_fd);
}
