#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(char *path, char *target, int* found) {
  char buf[512], *p;
  int fd;
  struct dirent de;  //file or folder to check name
  struct stat st;

  //open to check if path exists and get id of file/folder
  fd = open(path, O_RDONLY);
  if (fd < 0) return;  //path does not exist

  //get status of file/folder
  fstat(fd, &st);
  //close and return if the openned entry is not a folder
  if (st.type != T_DIR) {
      close(fd);
      return;
  }

  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/'; //add '/' at the end of the path

  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0) continue;  //entry is empty (deleted)
    //. is current directory, .. is previous directory, they exist in every folder
    if (!strcmp(de.name, ".") || !strcmp(de.name, "..")) continue;

    strcpy(p, de.name);

    //stat opens the file/folder to chech if it exists
    if (stat(buf, &st) < 0) continue;

    if (st.type == T_DIR) {
      find(buf, target, found); // recurse into subdirectory
    }
    else if (strcmp(de.name, target) == 0) {
      printf("%s\n", buf); // match found
      *found = 1;
    }
  }

  close(fd);
}

int main(int argc, char *argv[]) {

  if(strcmp(argv[1], "?") == 0) {
    printf("Usage: find directory file_name\n");
    exit(0);
  }

  if (argc != 3) {
    printf("Error: invalid number of arguments\n");
    exit(0);
  }

  int found = 0;
  find(argv[1], argv[2], &found);
  if(!found)
  {
    printf("File not found\n");
  }
  exit(0);
}
