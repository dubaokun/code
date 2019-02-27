#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include "testinterface.h"


void print_usage(void)
{
    printf("Usage: myso SO_PCGrandSonTH/n");
}

int main(int argc, char *argv[])
{
    if (2 != argc) {
        print_usage();
        exit(0);
    }

    const char *soname = argv[1];

	// 加载动态库
    void *so_handle = dlopen(soname, RTLD_LAZY);
    if (!so_handle) {
        fprintf(stderr, "Error: load so `%s' failed.\n", soname);
        exit(-1);
    }

	// 创建类
    dlerror();
    create_t *create = (create_t*) dlsym(so_handle, "create");
    char *err = dlerror();
    if (NULL != err) {
        fprintf(stderr, "%s\n", err);
        exit(-1);
    }
    CBase *pa = create();

	// 使用类
    pa->a = 57;
    pa->b = 3;
    //pa->c = 4;
    printf("CGrandSon.add(57, 3)=%d\n", pa->add()); // 注意，这里通过虚函数实现了
                                            // 对CGrandSon::add()的调用。

	// 卸载动态库
    destory_t *destory = (destory_t*) dlsym(so_handle, "destory");
    err = dlerror();
    if (NULL != err) {
        fprintf(stderr, "%s\n", err);
        exit(-1);
    }
    destory(pa);
    pa = NULL;

    dlclose(so_handle);

    printf("DONE!\n");
    return 0;
}
