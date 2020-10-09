#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>
int main()
{
    int shmid, n;
    char *shmptr;
    if (fork() == 0)
    {
        sleep(5); //todo: make a structure with flag and set the flag to 1

        if ((shmid = shmget(2041, 32, 0)) == -1)
            exit(1);
        shmptr = shmat(shmid, 0, 0);
        if (shmptr == (char *)-1)
        {
            exit(2);
        }
        printf("Child is reading\n");
        for (n = 0; n < 26; n++)
        {
            putchar(shmptr[n]);
        }
        putchar('\n');
    }
    else
    {
        if ((shmid = shmget(2041, 32, 0666 | IPC_CREAT)) == -1)
            exit(3);
        shmptr = shmat(shmid, 0, 0);
        if (shmptr == (char *)-1)
        {
            exit(4);
        }
        for (n = 0; n < 26; n++)
        {
            shmptr[n] = 'a' + n;
        }
        printf("Parent writing:\n");
        for (n = 0; n < 26; n++)
        {
            putchar(shmptr[n]);
        }
        putchar('\n');
        wait(NULL);
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            exit(5);
        }
    }
    return 0;
}