#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<sys/shm.h>
#include<stdio.h>
struct buf{
    int adminsize;
    int admin[100];
    
    int playersize[10];
    int player[10][10];
    
    int count;
    int result;
    
    int flag;
};
int search(int val, int player_no, struct buf * shmptr)
{

    int l = 0;
    int r = shmptr->playersize[player_no]-1;
    while(l <= r)
    {
        int mid = l + (r-l)/2;
        if(val == shmptr->player[player_no][mid])
        {
           // printf("hua %d, %d\n",val,player_no);
            //fflush(stdout);
            return 1;
        }
        if(val > shmptr->player[player_no][mid])
        {
             l = mid+1;
        }
        else{
            r = mid-1;
        }
    }
    
    //printf("nhi hua %d %d\n",val, player_no);
//     for(int i = 0; i < shmptr->playersize[player_no]; i++)
//     {
//         printf("p%d ",shmptr->player[player_no][i]);
//     }
    //printf("\n");
    //fflush(stdout);
    
    return 0;
    
}
int compare_fun(const void* a,const void* b)
{
    return *(int*)a > *(int*)b;
}
int main()
{
    int shmid;
    struct buf*shmptr = NULL;
    if((shmid = shmget(204, 10000, 0666| IPC_CREAT )) == -1)
    {
        perror("shmget fail\n");
        exit(4);
    }
    shmptr = shmat(shmid,0,0);
    if(shmptr == (struct buf*)-1)
        {
            perror("shmat fail\n");
            exit(2);
        }
    shmptr->flag = 0;
    shmptr->count = 100000;
        
    pid_t pid;
    int n_players;
    scanf("%d" ,&n_players);

    int player_no = 0;
    for(int i = 0; i < n_players; i++)
    {
        
        if((pid = fork()) == 0)
        {
            player_no = i;
            break;
        }
        
    }
    if(pid == 0)
    {
        if((shmid = shmget(204, 10000, 0)) == -1){
            perror("shmget fail\n");
            exit(1);
        }
        shmptr = shmat(shmid,0,0);
        while(shmptr->flag != 1);
        int main_count = 0;
        for(int i = 0; i < shmptr->adminsize; i++)
        {
             if(search(shmptr->admin[i], player_no, shmptr) != 0)
            {
                   //printf(" %d Value: %d for process#: %d\n", i,shmptr->admin[i], player_no);
                  // fflush(stdout);
                    main_count++;
                    if(main_count == shmptr->playersize[player_no])
                    {
                        if(main_count < shmptr->count)
                        {
                         shmptr->count = main_count;
                         shmptr->result = player_no;
                        }
                        return main_count;
                    }
            }
        }
        return 255;
    }
    else{
        //take input
        for(int i = 0; i < n_players; i++)
        {
            scanf("%d",&shmptr->playersize[i]);
            for(int j = 0; j < shmptr->playersize[i]; j++)
            {
                scanf("%d",&shmptr->player[i][j]);
            }
            qsort(shmptr->player[i],shmptr->playersize[i],sizeof(int), compare_fun);
        }
        //get admin input
        
        scanf("%d",&shmptr->adminsize);
        for(int i = 0; i < shmptr->adminsize;i++)
        {
            scanf("%d",&shmptr->admin[i]);
        }
        //fflush(stdin);
        shmptr->flag=1;
        
        
        int player_array[n_players];
        for(int i = 0; i < n_players; i++)
        {
            player_array[i] = 0;
        }
        for(int i =0 ; i < n_players; i++)
        {
            wait(NULL);
        }
        
        int min = 100000;
        int index = -1;
        /*
        for(int i = 0; i < n_players; i++)
        {
            printf("p:%d\n",player_array[i]); 
            if(min > player_array[i])
            {
                index = i;
                min = player_array[i];
            }
        }
        */
       // printf("count %d\n", shmptr->count);
        printf("player %d\n",shmptr->result+1);
        
        if(shmctl(shmid, IPC_RMID, NULL)==-1)
        {
            perror("shmctl error\n");
            exit(3);
        }
        return 0;
    }
}
