/**
 * gcc direct_io_read_file.c -o direct_io_read_file -D_GNU_SOURCE
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


// open the file in the direct mode
bool open_file(const char * filename)
{
	g_fd = open(filename, O_RDONLY | O_DIRECT);
	if (g_fd < 0) return false;
	return true;
}


// data_pos_absolute: the offset in the file; data_length: the length in the file; data_pos_align_absolute: the align offset int the file; block_size: the read block size
int get_infos(size_t data_pos_absolute, int data_length, size_t& data_pos_align_absolute, int& block_size)
{
	if (data_pos_absolute < 0 || data_length <= 0) return -1;
	size_t start_align_pos = data_pos_absolute / BLOCK_SIZE;
	size_t end_align_pos = ((data_pos_absolute +  data_length) / BLOCK_SIZE) + ((((data_pos_absolute +  data_length) % BLOCK_SIZE) == 0)?0:1); 
	
	data_pos_align_absolute = start_align_pos * BLOCK_SIZE;
	block_size = end_align_pos - start_align_pos;
	
	return 0;
}

// read file content in direct IO mode
int read_file(size_t start, int length, char * buffer)
{
	size_t data_pos_align_absolute = 0;
	int block_size = 0;
	
	int ret = get_infos(start, length, data_pos_align_absolute, block_size);
	if (0 != ret) return -1;
	if (0 >= block_size) return -2;
	if (start < data_pos_align_absolute) return -3;

	cout << "start " << start << endl;
	cout << "length " << length << endl;
	cout << "data_pos_align_absolute " << data_pos_align_absolute << endl;
	cout << "block_size " << block_size << endl;
	
   	unsigned char *buf;
   	ret = posix_memalign((void **)&buf, BLOCK_SIZE, block_size * BLOCK_SIZE);
    if (ret) {
       	return -4;
    }

	ret = pread(g_fd, buf, block_size * BLOCK_SIZE, data_pos_align_absolute);
	if (ret < length) throw std::runtime_error("length error");
			
	memcpy(buffer, buf + start - data_pos_align_absolute, length); 
			
    free(buf);
	return 0;
}

void test()
{
	size_t data_pos_absolute = 1172;
	int data_length = 2924;
	size_t data_pos_align_absolute = 0;
	int block_size = 0;
	
	int ret = get_infos(data_pos_absolute, data_length, data_pos_align_absolute, block_size);
	cout << "ret " << ret << endl;
	cout << "data_pos_align_absolute " << data_pos_align_absolute << endl;
	cout << "block_size "  << block_size << endl;

}

int main()
{
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

		std::cout << index -1 << "  =============================" << std::endl;
		char buffer[40960] = {0};
		int ret = read_file(start, length, buffer);		
			
		std::cout << "ret " << ret << " read size=" << strlen(buffer) << std::endl;
		//std::cout << buffer << std::endl;

		if ('#' != buffer[0]) throw std::runtime_error("head error");
		if ('#' != buffer[strlen(buffer) - 1]) throw std::runtime_error("tail error");
		for (int i = (1 + index) ; i < strlen(buffer) - 1; ++i) {
			if ('b' != buffer[i])
				throw std::runtime_error("content error");
		}
		
		char buff[1024] = {0};
		char * bufftemp = strchr(buffer, 'b');
		memcpy(buff, buffer+1, bufftemp - buffer - 1); 	
		cout << "index " << buff << endl;
				
		++ index;	
	}

	fclose(fp);
    close(g_fd);
}
