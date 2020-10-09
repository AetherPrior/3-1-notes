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

    if ((key = ftok("msg-q-writer.c", 'B')) == -1)
    {
        perror("Error in ftok\n");
        exit(1);
    }
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1)
    {
        perror("Error in msgget\n");
        exit(2);
    }

    printf("Enter lines of text. Press ^D to quit:\n");
    buf.mtype = 1;
    while (fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL)
    {
        int len = strlen(buf.mtext);
        if (buf.mtext[len - 1] == '\n')
        {
            buf.mtext[len - 1] = '\0';
        }
        if (msgsnd(msqid, &buf, len + 1, 0) == -1)
        {
            perror("Error in msgsnd\n");
            exit(3);
        }
    }
    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
        perror("Error in msgctl\n");
        exit(4);
    }
}
