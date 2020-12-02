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
    char *addr;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    size_t length, s;

    if (argc < 3 || argc > 4)
    {
        fprintf(stderr, "%s file offset [length]\n", argv[0]);
        exit(-1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error in open ");
    }
    if (fstat(fd, &sb) == -1)
    {
        perror("Error in fstat: ");
    }
    if (!S_ISREG(sb.st_mode))
    {
        fprintf(stderr, "%s is not a regular file\n", argv[1]);
        exit(1);
    }
    offset = atoi(argv[2]);
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1); //gives the page offset acc to page size

    if (offset >= sb.st_size)
    {
        perror("offset is past the EOF ");
        exit(1);
    }
    if (argc == 4)
    {
        length = atoi(argv[3]);
        if (offset + length > sb.st_size)
            length = sb.st_size - offset;
    }
    else
    {
        length = sb.st_size - offset;
    }
    addr = mmap(NULL, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);
    if (addr == MAP_FAILED)
    {
        perror("Error in mmap: ");
    }

    s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
    printf("Bytes written: %d, bytes to be written %d\n", s, length);
    if (s != length)
    {
        printf("%d %d\n", s, length);
        if (s == -1)
        {
            perror("Error in writing: ");
        }
        else if (s < length)
        {
            perror("Partial write: ");
        }
        else
        {
            perror("u w0t ");
        }
    }
    munmap(addr, length + offset - pa_offset);
    close(fd);
    return 0;
}