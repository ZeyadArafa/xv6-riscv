#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define NPROCESS 4

int main(int argc, char *argv[]) {

  int pid;
  int k;
  int z;
  char buffer_src[1024], buffer_dst[1024];
  int total_ta=0, total_w=0;
  int priorities[NPROCESS]={5, 2, 7, 1};
  int steps[NPROCESS]={10000000, 10000000, 10000000, 1000000};


  for (k = 0; k < NPROCESS; k++) {
    // ensure different creation times (proc->ctime)
    // needed for properly testing FCFS scheduling
    sleep(2);

    pid = fork();
    if (pid < 0) {
      printf("%d failed in fork!\n", getpid());
      exit(0);

    }
    else if (pid == 0) {
      // child
      set_priority(getpid(), priorities[k]);
      printf("[pid=%d] created  priority=%d\n", getpid(), priorities[k]);
      for (z = 0; z < steps[k]; z += 1) {
         // copy buffers one inside the other and back
         // used for wasting cpu time
         memmove(buffer_dst, buffer_src, 1024);
         memmove(buffer_src, buffer_dst, 1024);
      }
      exit(0);
    }
  }

  for (k = 0; k < NPROCESS; k++) {
    int tatime, wtime;
    pid = waitx(0, &tatime, &wtime);
    total_ta += tatime;
    total_w += wtime;
    printf("[pid=%d] terminated   TA=%d   W=%d\n", pid, tatime, wtime);
  }

  int avg_ta = total_ta/NPROCESS;
  int avg_w = total_w/NPROCESS;
  printf("Avg turnaround time = %d,  Avg waiting time = %d\n", avg_ta, avg_w);

  exit(0);
}
