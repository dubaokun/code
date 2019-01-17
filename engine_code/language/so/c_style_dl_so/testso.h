#ifndef _TESTSO_H_
#define _TESTSO_H_

extern "C" {
    int myadd(int a, int b);
    typedef int myadd_t(int, int); // myadd function type
}

#endif // _TESTSO_H_
