#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main( int argc ,char *argv[]){
  printf("%d\n", randLCG());
  exit(0);
}
