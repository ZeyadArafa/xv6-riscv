#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/fs.h"

int main( int argc ,char *argv[])
{
  if(strcmp(argv[1], "?") == 0) {
    printf("Usage: touch path\n");
    exit(0);
  }

  int file = open(argv[1], O_RDONLY);
  if(file >= 0)
  {
    printf("Error: file already exists\n");
    close(file);
    exit(0);
  }

  file = open(argv[1], O_CREATE);
  if(file < 0)
  {
    printf("Error: failed to create file\n");
  }
  else
  {
    printf("%s is created\n", argv[1]);
  }
  close(file);
  exit(0);
}
