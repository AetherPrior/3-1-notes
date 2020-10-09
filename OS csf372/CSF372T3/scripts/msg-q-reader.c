#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf
{
    long mtype;
    char mtext[200];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;
    
    if((key = ftok("msg-q-writer.c",'B')) == -1)
    {
        perror("Error in ftok\n");
        exit(1);
        
    }
    if((msqid = msgget(key, 0644)) == -1)
    {
        perror("Error in msgget\n");
        exit(2);
    }
    
    printf("Reader is reading:\n");
    while(1)
    {
        if(msgrcv(msqid, &buf, sizeof(buf.mtext),0, 0) == -1){
        
            perror("Error in msgrcv\n");
            exit(3);
        }
        printf("Reader: \"%s\"\n",buf.mtext);
    }       
}
