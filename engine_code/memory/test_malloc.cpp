#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void program_break_test(int count) {
  printf("%p\n", sbrk(0));

  char *bl = (char *)malloc(count * 1024);
  printf("%10p\n", sbrk(0));
  printf("malloc'd at: %10p\n", bl);

  free(bl);
  printf("%10p\n", sbrk(0));

}

int main(int argc, char **argv) {
    int count = atoi(argv[1]);
  program_break_test(count);
  return 0;
}
