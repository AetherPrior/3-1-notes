#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(void)
{
    char str1[] = "string 1";
    char str2[] = "string 2";
    int parpid = getpid(), childpid;

    char *anon /*anonymous mapping*/,
        *zero /*zero-back mapping*/;

    int fd;
    if ((fd = open("/dev/zero", O_RDWR, 0)) == -1)
    {
        perror("Error in open\n");
    }
    anon = (char *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    zero = (char *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (anon == MAP_FAILED || zero == MAP_FAILED)
    {
        if (zero == MAP_FAILED)
        {
            perror("Error in mmap\n");
        }
        else
        {
            perror("Error in anon: ");
        }
        exit(1);
    }
    strcpy(anon, str1);
    strcpy(zero, str1);
    printf("PID %d | anonymous: %s| zero-backed: %s\n", parpid, anon, zero);
    if (fork())
    {
        sleep(2);
        strcpy(anon, str2);
        strcpy(zero, str2);
        printf("PID %d | anonymous: %s| zero-backed: %s\n", parpid, anon, zero);
        munmap(anon, 4096);
        munmap(zero, 4096);
        close(fd); // closing the fd doesn't unmap

        return 0;
    }
    else
    {
        childpid = getpid();
        printf("PID %d | anonymous: %s| zero-backed: %s\n", childpid, anon, zero);
        sleep(3);
        printf("PID %d | anonymous: %s| zero-backed: %s\n", childpid, anon, zero);
        munmap(anon, 4096);
        munmap(zero, 4096);
        close(fd);
        return 0;
    }
}
