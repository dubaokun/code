#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include "testso.h"

// for dynamic library函数

void print_usage(void)
{
    printf("Usage: main SO_PATH/n");
}

int main(int argc, char *argv[])
{
    if (2 != argc) {
        print_usage();
        exit(0);
    }

    const char *soname = argv[1];

    void *so_handle = dlopen(soname, RTLD_LAZY); // 载入.so文件
    if (!so_handle) {
        fprintf(stderr, "Error: load so `%s' failed./n", soname);
        exit(-1);
    }

    dlerror(); // 清空错误信息
    myadd_t *fn = (myadd_t*)dlsym(so_handle, "myadd"); // 载入函数
    char *err = dlerror();
    if (NULL != err) {
        fprintf(stderr, "%s/n", err);
        exit(-1);
    }

    printf("myadd 57 + 3 = %d/n", fn(57, 3)); // 调用函数

    dlclose(so_handle); // 关闭so句柄
    return 0;
}
