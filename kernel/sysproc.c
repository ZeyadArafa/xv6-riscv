#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_getppid(void)
{
  return myproc()->parent->pid;
}

//used to measure scheduler metrics
uint64
sys_waitx(void)
{
  uint64 tatime_addr, wtime_addr;
  uint64 p;
  argaddr(0, &p);
  argaddr(1, &tatime_addr);
  argaddr(2, &wtime_addr);

  int tatime, wtime;
  int pid = waitx(p, &tatime, &wtime);

  if (copyout(myproc()->pagetable, tatime_addr, (char *)&tatime, sizeof(int)) < 0)
    return -1;
  if (copyout(myproc()->pagetable, wtime_addr, (char *)&wtime, sizeof(int)) < 0)
  return -1;

  return pid;
}

uint64
sys_set_priority(void)
{
  int pid, priority;
  argint(0, &pid);
  argint(1, &priority);
  return set_priority(pid, priority);
}

uint64
sys_get_priority(void)
{
  int pid;
  argint(0, &pid);
  return get_priority(pid);
}

  // uint64
  // sys_getptable(void) {
  //   int n;
  //   uint64 buf = 0; // user pointer to struct procinfo array

  //   //pass arguments from user space to kernel space
  //   argint(0, &n);
  //   argaddr(1, &buf);

  //   if(n < 1 || buf == 0)
  //     return 0;

  //   struct procinfo ptable[n];
  //   getptable(n, ptable);

  //   if (copyout(myproc()->pagetable, buf, (char *)ptable, sizeof(struct procinfo) * n) < 0)
  //     return 0;

  //   return 1;
  // }
