#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

//volatile tells the compiler not to optimize reads from this pointer
//because the value can change at any time (e.g., the timer keeps counting up).
#define MTIME ((volatile uint64 *)CLINT_MTIME)

#ifndef BOOT_EPOCH
#define BOOT_EPOCH 0  // fallback if not defined
#endif


extern uint64 kbd_int_count;
extern uint64 sys_call_count;

uint64
sys_kbdint() {
  return kbd_int_count;
}

uint64
sys_countsyscall() {
  return sys_call_count;
}

static uint rand_seed = 1;
uint64
sys_randLCG(void)
{
  if (rand_seed == 1)
    rand_seed = *MTIME;

  rand_seed = rand_seed * 1103515245 + 12345; //used to generate 31-bit number
  //rand_seed/2^16 ---> make the number 15 bits
  return (rand_seed / 65536) % 32768; // 15-bit random number in the range [0, 32767]
}



static int is_leap(int y) {
  return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
}

static int month_lengths[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

void unix_to_date(uint64 ts, struct dt *r) {
  int sec = ts % 60; ts /= 60;
  int min = ts % 60; ts /= 60;
  int hr  = ts % 24; ts /= 24;


  int days = ts;
  int y = 1970;

  while (1) {
    int leap = is_leap(y);
    int days_in_year = 365 + leap;
    if (days < days_in_year)
      break;
    days -= days_in_year;
    y++;
  }

  int m = 0;
  while (1) {
    int days_in_month = month_lengths[m];
    //February has 29 days in case of leap year
    if (m == 1 && is_leap(y)) days_in_month++;
    if (days < days_in_month)
      break;
    days -= days_in_month;
    m++;
  }

  r->year = y;
  r->month = m + 1;
  r->day = days + 1;
  r->hour = hr + 3; //UTC+3
  r->minute = min;
  r->second = sec;
}


uint64
sys_datetime(void)
{
  struct dt r;
  uint64 dst;                  // user pointer

  // fetch user-provided pointer from syscall args
  argaddr(0, &dst);


  // read machine time (ticks)
  uint64 t = *MTIME;              // fault-safe after kvmmap
  uint64 secs_since_boot = t / 10000000;  //clock frequency = 10 MHz (10 million ticks/sec)
  uint64 now = BOOT_EPOCH + secs_since_boot;

  // convert to calendar date
  unix_to_date(now, &r);

  // copy back into user space
  if (copyout(myproc()->pagetable, dst, (char *)&r, sizeof(r)) < 0)
    return -1;

  return 0;
}
