#include <unistd.h>
#include "fcntl.h"
#include "sys/mman.h"
#include "sys/stat.h"
int main (int argc, char const* argv[])
{
    int fd = -1;
    fd = shm_open("test",O_CREAT|O_RDWR,S_IRUSR | S_IWUSR);
    if(fd < 0)
    {
        perror("shm_open failt ret :%d\n",fd);
        exit(-1);
    }
    ftruncate(fd,1024);
    char *ptr =(char *) mmap(NULL,1024,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    printf("%s\t%s\n",__FILE__,ptr);
    while(1)
    {
        gets(ptr);
    }
    return 0;
}
