#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main( int argc ,char *argv[])
{
  printf("%d system calls invoked since startup\n", countsyscall());
  exit(0);
}
