#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main( int argc ,char *argv[])
{
  printf("Current process: PID=%d PPID=%d\n", getpid(), getppid());

  struct procinfo ptable[64];

  if (getptable(64, ptable) == 0) {
    printf("getptable failed\n");
    exit(0);
  }

  printf("PID PPID STATE SIZE   NAME\n");
  for (int i = 0; i < 64 && ptable[i].pid != 0; i++) {
    printf("%d    %d    %d    %ld  %s\n", ptable[i].pid, ptable[i].ppid,
           ptable[i].state, ptable[i].sz, ptable[i].name);
  }

  exit(0);
}
