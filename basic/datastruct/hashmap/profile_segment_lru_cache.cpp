#ifndef __SEGMENT_HASH_H__
#define __SEGMENT_HASH_H__

#include <string>
#include <iostream>

#define SEGMENT_COUNT 1024
#define SEGMENT_SIZE (64 * SEGMENT_COUNT)

struct Segment {
	std::string _file_name;
	size_t _offset_pos;
	size_t _index;		
};

// calc the count of filename 
int calc_file_name_count(std::string str)
{
	int count = 0;
	for(int i = 0; i < str.size(); ++i)
		count += str[i];
	return count;
}

// to calc file aligned segment
int calc_file_segment(std::string& file_name, size_t& file_size)
{
	if (0 == file_name.size()) return -1;
	if (0 > file_size) return -2;
	
	// calc number by file_name to judge cycle from
	int tmp = calc_file_name_count(file_name) % 2;
	for (size_t i = 0; i < file_size; i+= SEGMENT_SIZE) {
		size_t change = i % (SEGMENT_SIZE * SEGMENT_COUNT);
		size_t index = change / SEGMENT_SIZE;
		if (0 == tmp) {
			std::cout << "offset=" << i << "index=" << index << std::endl;
		} else {
		} 			
	}

	return 0;
}

// to calc segment: 0 - SEGMENT_COUNT
int calc_offset_segment(const std::string& file_name, const size_t& offset_pos, const int& length)
{
	std::cout << "offset=" << offset_pos << " length=" << length << std::endl;
	if (0 == file_name.size()) return -1;
	if (0 > offset_pos) return -2;
	
	// to calc file offset segments
	int tmp = calc_file_name_count(file_name) % 2;
	size_t index_start = offset_pos / SEGMENT_SIZE;
	size_t index_end = (offset_pos + length - 1) / SEGMENT_SIZE;
	size_t pos = 0;
	int len = 0;
	int tmp_len = length;
	for (int i = index_start * SEGMENT_SIZE; i <= index_end * SEGMENT_SIZE; i+= SEGMENT_SIZE) {
		size_t change = i % (SEGMENT_SIZE * SEGMENT_COUNT);
		size_t index = change / SEGMENT_SIZE;
		
		if (index_start == index_end) {
				pos = offset_pos - i;
				len = length;
		} else { 
			if (i == index_start * SEGMENT_SIZE) {
				pos = offset_pos - i;
				len = SEGMENT_SIZE - pos;	
				tmp_len -= len;
			} else if (i < index_end * SEGMENT_SIZE) {
				pos = 0;
				len = SEGMENT_SIZE;
				tmp_len  -= len;
			} else {
				pos = 0;
				len = tmp_len;
			}
		}

		if (0 == tmp) {
			std::cout << "offset=" << i << "index=" << index << "||| segpos=" << pos << " seglen="<< len << std::endl;
		} else {
			std::cout << "offset=" << i << "index=" << SEGMENT_COUNT - 1 - index << "||| segpos=" << pos << " seglen="<< len << std::endl;
		}
	}

	return 0;
}


#endif
