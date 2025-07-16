#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main( int argc ,char *argv[])
{
  if(strcmp(argv[1], "?") == 0) {
    printf("Usage: fact integer\n");
    exit(0);
  }

  if (argc != 2) {
    printf("Error: invalid number of arguments\n");
    exit(0);
  }

  if(argv[1][0] == '-')
    {
      printf("Error: negative input not allowed\n");
      exit(0);
    }

  if(isNumber(argv[1]))
  {
    int n = atoi(argv[1]);
    int result = 1;
    for(int i = n; i>1; i--)
    {
      result *= i;
    }
    printf("factorial = %d\n",result);
  }
  else
  {
    printf("Error: invalid input\n");
  }

  exit(0);

}
