/*
 * crc64.h
 * Created on: 2012-12-31
 *      Author: yuanpeizhi
 * Modify by weilei: 2016-03-16
 */

#ifndef UTIL_CRC64_H_
#define UTIL_CRC64_H_

#define POLY64REV  0x95AC9329AC4BC9B5
#define INITIALCRC 0xFFFFFFFFFFFFFFFF

#include <iostream>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "openssl/md5.h"

inline void crc64(const char*seq, unsigned int lg_seq, uint64_t *pFinalCrc)
{
	unsigned short i;
	unsigned char j;
	uint64_t crc = INITIALCRC;
	uint64_t part;
	static bool init = false;
	static uint64_t CRCTable[256];

	if (!init) {
		init = true;
		for (i = 0; i < 256; i++) {
			part = i;
			for (j = 0; j < 8; j++) {
				if (part & 1)
					part = (part >> 1) ^ POLY64REV;
				else
					part >>= 1;
			}
			CRCTable[i] = part;
		}
	}

	while (lg_seq-- > 0)
		crc = CRCTable[(crc ^ *seq++) & 0xff] ^ (crc >> 8);

	*pFinalCrc = crc;

	return;
}

inline void crc64(const std::string &src, uint64_t *pFinalCrc)
{
    crc64(src.c_str(),(unsigned int)(src.length()), pFinalCrc);
    return;
}

/*
 * func : make a 64 bit string signature
 *
 * args : str, len, input string and its length
 *
 * ret  : 64 bit signature of the string,
 *        0L indicates wrong.
 */
inline uint64_t crc64(const char *str, int32_t len)
{
    if (str == NULL || len == 0) return 0;

	uint64_t sign[2];
	MD5((const unsigned char *) str, len, (unsigned char *) sign);
	uint64_t hash = sign[0] ^ sign[1];
    return hash;
}

#endif
