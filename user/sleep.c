#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"



int main( int argc ,char *argv[])
{
  if(argc != 2) {
    printf("Error: invalid number of arguments\n");
    exit(0);
  }

  if(strcmp(argv[1], "?")==0)
  {
    printf("Usage: sleep ticks\n");
    exit(0);
  }

  int time = atoi(argv[1]);
  printf("starting sleep for %d\n",time);
  sleep(time);
  printf("finished sleeping for %d\n",time);
  exit(0);

}
