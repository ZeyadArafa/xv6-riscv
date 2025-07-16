typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int  uint32;
typedef unsigned long uint64;

typedef uint64 pde_t;

struct dt {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
};

#define PNAME_LEN 16

struct procinfo {
  int pid;
  int ppid;
  int state;
  uint64 sz;
  char name[PNAME_LEN];
};
