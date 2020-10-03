#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void)
{
    char s[1000001];
    scanf("%s", s);
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Forking failed. Exiting\n");
    }
    else if (pid != 0)
    {
        //parent
        int retval;
        waitpid(-1, &retval, 0);
        if (retval)
        {
            printf("no");
        }
        else
        {
            printf("yes");
        }
    }
    else
    {
        //child
        int n = strlen(s) - 1;
        for (int i = 0; i < strlen(s) / 2; i++)
        {
            if (s[i] != s[n - i])
            {
                return 1;
            }
        }
    }
    return 0;
}