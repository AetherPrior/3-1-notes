#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/shm.h>
#include <stdio.h>
struct buf
{
    int result;
};
struct player
{
    int count;
    int numbers[100];
};
int compare(const void *a, const void *b)
{
    return *(int *)a > *(int *)b;
}
int binsearch(int val, int *arr, int size)
{
    int l = 0;
    int r = size - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (val == arr[mid])
        {
            return mid;
        }
        else if (val < arr[mid])
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return -1;
}
void delete_element(int index, int *count, int *arr, int playerno)
{
    for (int i = index; i < *count; i++)
    {
        arr[i] = arr[i + 1];
    }
    (*count)--;
}
int main()
{
    int n;
    scanf("%d", &n);
    struct player *p[n]; //n players each with sharedmem object.
    int playerids[n];
    for (int i = 0; i < n; i++)
    {
        int c;
        scanf("%d", &c);
        if ((playerids[i] = shmget(i * 10 + 3241, 1000, 0666 | IPC_CREAT)) == -1)
        {
            perror("rip");
            exit(1);
        }
        p[i] = shmat(playerids[i], 0, 0);
        p[i]->count = c;
        for (int j = 0; j < p[i]->count; j++)
        {
            scanf("%d", &p[i]->numbers[j]);
        }
        qsort(p[i]->numbers, p[i]->count, sizeof(int), compare);
    }
    int asize;
    scanf("%d", &asize);
    int admin[asize];
    for (int i = 0; i < asize; i++)
    {
        scanf("%d", &admin[i]);
    }
    pid_t pid;

    int shmid = 0;
    struct buf *shmptr;
    if ((shmid = shmget(2041, 100, 0666 | IPC_CREAT)) == -1)
    {
        exit(1);
    }
    shmptr = shmat(shmid, 0, 0);
    shmptr->result = -1;

    for (int i = 0; i < asize; i++)
    {
        int playerno = 0;
        for (int j = 0; j < n; j++)
        {
            if ((pid = fork()) == 0)
            {
                playerno = j;
                break;
            }
            else if (pid == -1)
            {
                perror("Error with fork");
                exit(2);
            }
        }
        if (pid == 0)
        {
            if ((shmid = shmget(2041, 100, 0666 | IPC_CREAT)) == -1)
            {
                exit(1);
            }
            if ((shmptr = shmat(shmid, 0, 0)) == (struct buf *)-1)
            {
                perror("rip2");
                exit(2);
            }
            if (shmptr->result != -1)
            {
                return 0;
            }
            int res;

            if ((playerids[playerno] = shmget(playerno * 10 + 3241, 1000, 0)) == -1)
            {
                perror("rip");
                exit(1);
            }
            if ((p[playerno] = shmat(playerids[playerno], 0, 0)) == (struct player *)-1)
            {
                perror("rip3");
                exit(3);
            }

            if ((res = binsearch(admin[i], p[playerno]->numbers, p[playerno]->count)) != -1)
            {
                delete_element(res, &p[playerno]->count, p[playerno]->numbers, playerno);
                if (p[playerno]->count == 0)
                {
                    shmptr->result = playerno;
                    exit(0);
                }
            }
            exit(0);
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                wait(NULL);
            }
            if (shmptr->result != -1)
            {
                printf("player %d", shmptr->result + 1);
                return 0;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (shmctl(playerids[i], IPC_RMID, NULL) == -1)
        {
            perror("RIp5");
            exit(5);
        }
    }
    shmctl(shmid, IPC_RMID, NULL);
}
