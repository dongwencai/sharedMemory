#include <unistd.h>
#include "fcntl.h"
#include "sys/mman.h"
#include "sys/stat.h"
int main (int argc, char const* argv[])
{
    int fd = -1;
    fd = shm_open("test",O_CREAT|O_TRUNC|O_RDWR,S_IRUSR | S_IWUSR);
    if(fd < 0)
    {
        perror("shm_open failt ret :%d\n",fd);
        exit(-1);
    }
    ftruncate(fd,1024);
    char *ptr =(char *) mmap(NULL,1024,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    ptr[0]='a';
    ptr[1]='\0';
    strcpy(ptr,"hello world");
    puts(ptr);
    while(1)
    {
        getchar();
        puts(ptr);
    }
    return 0;
}


/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/wait.h>

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  int r;

  const char *memname = "sample";
  const size_t region_size = sysconf(_SC_PAGE_SIZE);

  int fd = shm_open(memname, O_CREAT | O_TRUNC | O_RDWR, 0666);
  if (fd == -1)
    error_and_die("shm_open");

  r = ftruncate(fd, region_size);
  if (r != 0)
    error_and_die("ftruncate");

  void *ptr = mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED)
    error_and_die("mmap");
  close(fd);

  pid_t pid = fork();

  if (pid == 0) {
    u_long *d = (u_long *) ptr;
    *d = 0xdbeebee;
    exit(0);
  }
  else {
    int status;
    waitpid(pid, &status, 0);
    printf("child wrote %#lx/n", *(u_long *) ptr);
  }

  r = munmap(ptr, region_size);
  if (r != 0)
    error_and_die("munmap");

  r = shm_unlink(memname);
  if (r != 0)
    error_and_die("shm_unlink");

  return 0;
}*/
