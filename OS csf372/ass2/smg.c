#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
struct buf
{
    int vals[10];   //admin
    int valsize; //size of admin
    int flag;    //to check if set

    //int result;
    int count[10];

    int a[10][10];    //each player
    int sizes[10]; //sizes of each player array
};
int search(int index, int arg, int size, struct buf *shmptr)
{
    int l = 0;
    int val = shmptr->vals[index];
    int r = size - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (val == shmptr->a[arg][mid])
        {
            return 1;
        }
        if (val > shmptr->a[arg][mid])
        {
            l = mid + 1;
        }
        else if (val < shmptr->a[arg][mid])
        {
            r = mid - 1;
        }
    }
    return 0;
}
int compare(const void *a, const void *b)
{
    return *(int *)a > *(int *)b; 
}
int main(int argc, char **argv, char **envp)
{
    struct buf *shmptr = NULL;
    int shmid;
    int n;
    int arg = 0;
    scanf("%d", &n);
    pid_t pid;
    for (int i = 0; i < n; i++)
    {
        if ((pid = fork()) == 0)
        {
            arg = i;
            break;
        }
    }
    if (pid == 0)
    {
        if ((shmid = shmget(204, 10000, 0)) == -1)
            exit(1);
        shmptr = (struct buf *)shmat(shmid, 0, 0);
        if (shmptr == (struct buf *)-1)
        {
            exit(2);
        }
        while (shmptr->flag != 1)
            ;
        
        int c = 0;
        for (int i = 0; i < shmptr->valsize; i++)
        {
            if (search(i, arg,shmptr->sizes[arg], shmptr) != 0)
            {
                
                c++;
                if (c == shmptr->sizes[arg])
                {
                        printf("arg: %d i:%d\n",arg,i);
                        fflush(stdout);
                        shmptr->count[arg] = i;
                        break;
                }
            }
           
        }
        exit(0);
    }
    else
    {
        if ((shmid = shmget(204, 10000, 0666 | IPC_CREAT)) == -1)
            exit(3);
        shmptr = (struct buf *)shmat(shmid, 0, 0);
        shmptr->flag = 0; //to make sure it doesn't initially contain 1
        for(int i = 0; i < 10; i++)
            shmptr->count[i] = 0;
        if (shmptr == (struct buf *)-1)
        {
            exit(4);
        }
        for (int i = 0; i < n; i++)
        {
            int c;
            
            scanf("%d", &c);
           
            shmptr->sizes[i] = c;
            for (int j = 0; j < c; j++)
            {
                scanf("%d", &(shmptr->a[i][j]));
            }
            qsort(shmptr->a[i], c, sizeof(int), compare);
        }
        
        scanf("%d", &shmptr->valsize);


        for (int i = 0; i < shmptr->valsize; i++)
        {
            scanf("%d", &shmptr->vals[i]);
        }
       
        shmptr->flag = 1;
         for (int i = 1; i <= n+1; i++)
            wait(NULL);
        
        int min = 1000000;
        int index = 0;
        for(int i = 0; i < n; i++)
        {
             printf("%d",shmptr->count[i]);
            if(shmptr->count[i] < min)
            {
                index = i;
                min = shmptr->count[i];
            }
        }
        
        printf("player %d", index + 1);
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            exit(5);
        }
    }
}
