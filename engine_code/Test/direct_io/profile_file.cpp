#include "profile_file.h"
#include "file_util.h"
#include "GlobalAttribute.h"

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <new>

namespace profile
{

ProfileFile::ProfileFile(const char* filename)
{
	if (filename == NULL) {
		_filename[0] = '\0';
	}
	else {
		snprintf(_filename, PATH_MAX, "%s", filename);
	}
	_flag = FILE_READ;
	_size = 0;
	_offset = 0;
	_base = NULL;
	_fp   = NULL;
    _fd   = -1;
    _mem_zero = false;
	ext_file = NULL;
}

ProfileFile::~ProfileFile()
{
    close();
}

int ProfileFile::open(int flag, int length, int mode)
{
    if (_filename[0] == '\0' || _base != NULL) {
        return -1;
	}
	_flag = flag;
    _load_mode = mode;

	if (flag == FILE_DIRECT) {
		if ((_fd = ::open(_filename, O_RDONLY | O_DIRECT)) < 0) {
			return -21; 
		}
		_fp = NULL;			// only use fd
		length = 0;			// not allowed to write
	}
	else if (flag == FILE_READ) {
		if ((_fp = fopen(_filename, "rb")) == NULL) {
			return -2;
		}
		length = 0; //read的时候, legnth不起作用，强制清0
        _fd = fileno(_fp);
	}
	else if (flag == FILE_MODIFY) {
		if ((_fp = fopen(_filename, "rb+")) == NULL) {
			return -3;
		}
        _fd = fileno(_fp);
	}
	else if (flag == FILE_WRITE) {
		if (util::makedir(_filename) != 0) {
			return -4;
		}
		if ((_fp = fopen(_filename, "wb")) == NULL) {
			return -5;
		}
		if (length > 0) {
			_base = new (std::nothrow) char[length];
			if (_base == NULL) return -6;
            if (_mem_zero)
                memset(_base, 0, length);
			_size = length;
		}
        _fd = fileno(_fp);
		return 0;
	}
	else {
		return -7;
	}

	struct stat st;
	if (stat(_filename, &st) < 0) {
		return -8;
	}
	_size = st.st_size;
    if (mode == MODE_FULL_MEMORY) {
        _base = new (std::nothrow) char[_size + length];
        if (_base == NULL) return -9;
        if (_size > 0 && fread(_base, _size, 1, _fp) != 1) {
            return -10;
        }
        posix_fadvise(_fd, 0, 0, POSIX_FADV_DONTNEED);
    }
	_offset = _size;  //设置为file size强迫modify只能追加length
	_size += length;
	return 0;
}

int ProfileFile::flush()
{
    if (_flag == FILE_READ || _fp == NULL) {			// when flag=FILE_DIRECT, _fp=NULL
        return -1;
	}
   	if (_base) {
		if (fseek(_fp, 0, SEEK_SET) != 0) return -2;
		if (fwrite(_base, _size, 1, _fp) != 1) {
			return -3;
		}
	}
	return fflush(_fp);
}

int ProfileFile::close()
{
    int ret = 0;
	if (_flag == FILE_DIRECT && ::close(_fd) != 0) {
		ret = -1;
	}
    if (_fp != NULL && ::fclose(_fp) != 0) {
        ret = -1;
    }
	_fp = NULL;
    _fd = -1;
	if (_base) {
		delete[] _base;
		_base = NULL;
	}
    _size = 0;
	_offset = 0;
    return ret;
}

int ProfileFile::write(const void *src, size_t len)
{
	if (_flag == FILE_DIRECT) return -21;
	if (_flag == FILE_READ) return -1;

	if (_base == NULL) {
		if (fseek(_fp, 0, SEEK_END) != 0) return -2;
		if (fwrite(src, len, 1, _fp) != 1) {
			fprintf(stderr, "write fail, err=%s\n", strerror(errno));
			return -3;
		}
	}
	else {
		if (_offset + len > _size) {
			fprintf(stderr, "max size=%ld. current offset=%ld, len=%ld\n",
					_size, _offset, len);
			return -4;
		}
		memcpy(_base + _offset, src, len);
	}
	_offset += len;
    return 0;
}

int ProfileFile::write(size_t pos, const void *src, size_t len)
{
	if (_flag == FILE_DIRECT) return -21;
	if (_flag == FILE_READ) return -1;

	if (_base == NULL) {
		if (fseek(_fp, pos, SEEK_SET) != 0) return -2;
		if (fwrite(src, len, 1, _fp) != 1) {
			fprintf(stderr, "write fail, err=%s\n", strerror(errno));
			return -3;
		}
	}
	else {
		if (pos + len > _size) {
			fprintf(stderr, "max size=%ld. current offset=%ld, len=%ld\n",
					_size, pos, len);
			return -4;
		}
		memcpy(_base + pos, src, len);
	}
	return 0;
}

int ProfileFile::read(size_t pos, void *src, size_t len)
{
    if (_load_mode == MODE_FULL_MEMORY) {
        if (pos + len > _size || _base == NULL) {
            return -1;
        }
        memcpy(src, _base + pos, len);
        return 0;
    }

	if (_flag == FILE_DIRECT) {
		if (pos < 0 || len <= 0 || pos + len > _size) return -21;
		int pagesize = getpagesize();
		if (pagesize < DEFAULT_BLOCK_SIZE) pagesize = DEFAULT_BLOCK_SIZE;
		size_t aligned_block_begin = pos / pagesize;
		size_t aligned_block_end = ((pos + len) / pagesize) + ((((pos + len) % pagesize) == 0)?0:1);
		size_t aligned_pos_begin = aligned_block_begin * pagesize;
		int aligned_length = (aligned_block_end - aligned_block_begin) * pagesize;

		char * buf;
		int ret = posix_memalign((void **)&buf, pagesize, aligned_length);
		if (0 != ret) return -22;

		ret = pread(_fd, buf, aligned_length, aligned_pos_begin);
		if ((ret - (pos - aligned_pos_begin)) < len) return -23;
		memcpy(src, buf + pos - aligned_pos_begin, length);

		return 0;

	} else {
        size_t left = len;
        ssize_t r = -1;
        char* ptr = static_cast<char*>(src);
        while (left > 0) {
            r = pread(_fd, ptr, left, static_cast<off_t>(pos));
            if (r <= 0) {
                if (r == -1 && errno == EINTR) {
                    continue;
                }
                break;
            }
            ptr += r;
            pos += r;
            left -= r;
        }

        if (left == 0)
            return 0;
        return -1;
    }
}

int ProfileFile::dump(const char* filename)
{
    if (filename[0] == '\0' || _base == NULL) {
        return -1;
    }
    FILE*  fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        return -3;
    }
    if (fwrite(_base, _size, 1, fp) != 1)
    {
        return -4;
    }

    return fclose(fp);
}

int ProfileFile::dump(const char* filename, int len)
{
    if (filename[0] == '\0' || _base == NULL) {
        return -1;
    }
    FILE*  fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        return -3;
    }
    if (fwrite(_base, len, 1, fp) != 1)
    {
        return -4;
    }

    return fclose(fp);
}

int ProfileFile::load(const char* filename)
{
    if (filename[0] == '\0' || _base == NULL) {
        return -1;
    }

    FILE*  fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        return -2;
    }
    fseek(fp,0L,SEEK_END);
    uint32_t len = ftell(fp);
    rewind(fp);
    if (len > _size)
    {
        fprintf(stderr, "[ProfileFile::load] max size=%ld. offset=%ld, len=%u\n",
                _size, _offset, len);
        return -3;
    }

    if (fread(_base, len, 1, fp) != 1)
    {
        return -4;
    }

    _offset = len;

    posix_fadvise(fileno(fp) , 0, 0, POSIX_FADV_DONTNEED);
    return fclose(fp);
}

void ProfileFile::invalidPageCache(size_t offset)
{
    //fprintf(stderr, "Invalid Page Cache of %s\n", _filename);
	if (_flag == FILE_DIRECT)
		return;
    posix_fadvise(_fd, 0, offset, POSIX_FADV_DONTNEED);
}

}
