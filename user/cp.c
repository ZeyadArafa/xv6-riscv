#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {

  if(strcmp(argv[1], "?") == 0) {
    printf("Usage: cp source_file destination_file\n");
    exit(0);
  }

  if (argc != 3) {
    printf("Error: invalid number of arguments\n");
    exit(0);
  }

  int src = open(argv[1], O_RDONLY);
  if (src < 0) {
    printf("Error: cannot open %s\n", argv[1]);
    exit(0);
  }

  int dst = open(argv[2], O_CREATE | O_WRONLY);
  char buf[512];
  int n;

  while ((n = read(src, buf, sizeof(buf))) > 0) {
    write(dst, buf, n);
  }

  printf("%s copied into %s\n", argv[1], argv[2]);
  close(src);
  close(dst);
  exit(0);
}
