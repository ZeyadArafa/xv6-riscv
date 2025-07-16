#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main( int argc ,char *argv[])
{
  printf("Number of keyboard interrupts = %d\n", kbdint());

  exit(0);

}
