#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {

  if(strcmp(argv[1], "?") == 0) {
    printf("Usage: mv source_path destination_path\n");
    exit(0);
  }

  if (argc != 3) {
    printf("Error: invalid number of arguments\n");
    exit(0);
  }

  char *src = argv[1];
  char *dst = argv[2];

  // Create a new link (new name) for the source file
  if (link(src, dst) < 0) {
    printf("Error: failed to link '%s' to '%s'\n", src, dst);
    exit(0);
  }

  // Remove the original source file name
  if (unlink(src) < 0) {
    printf("Warning: linked '%s' to '%s' but failed to remove '%s'\n", src, dst, src);
    exit(0);
  }

  printf("%s moved to %s\n", argv[1], argv[2]);
  exit(0);
}
