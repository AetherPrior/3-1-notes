#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    struct stat sb;
    off_t len;
    char *p;
    int fd;
    if (argc < 2)
    {
        fprintf(stderr, "usage is %s <file>\n", argv[0]);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error in open ");
    }
    if (fstat(fd, &sb) == -1)
    {
        perror("Error in fstat ");
    }
    if (!S_ISREG(sb.st_mode)) /* if(sb.st_mode != S_ISREG)*/
    {
        fprintf(stderr, "%s is not a regular file\n", argv[1]);
        exit(1);
    }
    p = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
        perror("Error in mmap: ");
    }
    close(fd);
    for (len = 0; len < sb.st_size; len++)
    {
        putchar(p[len]);
    }
    munmap(p, sb.st_size);
    return 0;
}