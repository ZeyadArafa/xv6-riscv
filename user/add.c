#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main( int argc ,char *argv[])
{
  if(strcmp(argv[1], "?") == 0) {
    printf("Usage: add number1 number2\n");
    exit(0);
  }

  if(argc != 3) {
    printf("Error: You can only add two numbers\n");
    exit(0);
  }

  if(isNumber(argv[1]) && isNumber(argv[2]))
  {
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    int sum = n1+n2;

    printf("sum = %d\n",sum );
  }
  else
  {
    printf("Error: invalid input\n");
  }

  exit(0);

}
