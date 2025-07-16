#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main( int argc ,char *argv[])
{
  struct dt dateTime;

  datetime(&dateTime);
  printf("%d %d %d %d %d %d\n", dateTime.year, dateTime.month, dateTime.day,
    dateTime.hour, dateTime.minute, dateTime.second);
}
