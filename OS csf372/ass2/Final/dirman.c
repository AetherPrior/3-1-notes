#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
struct File
{
    char permission[4];
    char name[51];
};
char perms[8][4] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
struct File filarr[1000];
int size = -1;
int pfds[2];
char buf[1001];
void ls(char *dirname)
{
    close(pfds[0]);
    for (int i = 0; i <= size; i++)
    {
        if (dirname != NULL)
        {
            char newdir[100];
            char *nextdir = newdir + 1;
            strcpy(nextdir, dirname);
            newdir[0] = '/';
            newdir[strlen(newdir) + 1] = '\0';
            newdir[strlen(newdir)] = '/';
            if (strstr(filarr[i].name, newdir) != NULL)
            {
                if (write(pfds[1], filarr[i].name, strlen(filarr[i].name)) == -1)
                {
                    perror("rip pipe: ");
                };
                if (write(pfds[1], "\n", 1) == -1)
                {
                    perror("rip pipe: ");
                };
            }
        }
        else
        {
            if (write(pfds[1], filarr[i].name, strlen(filarr[i].name)) == -1)
            {
                perror("rip pipe: ");
            };
            write(pfds[1], "\n", 1);
        }
    }
    close(pfds[1]);
}
void chmod(char *name, int p)
{
    for (int i = 0; i <= size; i++)
    {
        if (!strcmp(filarr[i].name, name))
        {
            if (p < 0)
            {
                char *per = filarr[i].permission;
                if ((-p) & 4)
                {
                    per[0] = '-';
                }
                if ((-p) & 2)
                {
                    per[1] = '-';
                }
                if ((-p) & 1)
                {
                    per[2] = '-';
                }
            }
            strncpy(filarr[i].permission, perms[p], 4);
        }
    }
}
void ronly(char *dirname)
{
    open(pfds[1]);
    close(pfds[0]);
    for (int i = 0; i <= size; i++)
    {
        struct File tok = filarr[i];
        if (dirname != NULL)
        {
            if (strstr(filarr[i].name, dirname) == NULL)
            {
                tok.name[0] = '\0';
            }
        }
        if (tok.name[0] != '\0')
        {
            if (!strncmp(tok.permission, "r--", 3))
            {
                char str[1000];
                strncpy(str, tok.name, strlen(tok.name) + 1);
                strcat(str, "\n");

                if (write(pfds[1], str, strlen(str)) == -1)
                {
                    perror("pipe rip\n");
                }
            }
        }
    }
    close(pfds[1]);
}
void search(char *name)
{
    close(pfds[0]);
    for (int i = 0; i <= size; i++)
    {
        if (strstr(filarr[i].name, name) != NULL)
        {
            char str[100];
            strncpy(str, filarr[i].name, strlen(filarr[i].name) + 1);
            strcat(str, "\n");
            write(pfds[1], str, strlen(str));
        }
    }
    close(pfds[1]);
}
void add(char *filename)
{
    size++;
    strcpy(filarr[size].name, filename);
    strcpy(filarr[size].permission, perms[4]);
}
void add_entry(char *perms, char *filename)
{
    size++;
    strncpy(filarr[size].permission, perms, 4);
    strcpy(filarr[size].name, filename);
}
void add_handler(char *cmd)
{
    char *token = strtok(cmd, " "), *token2 = strtok(NULL, " ");
    add_entry(token, token2);
}
void cmdhandler(char *cmd)
{
    char *token = strtok(cmd, " ");
    char *token2 = strtok(NULL, " ");
    int pid = -123;
    if (!strncmp(token, "ls", 2))
    {
        if (pipe(pfds) == -1)
        {
            perror("pipe rip\n");
            exit(1);
        }
        pid = fork();
        if (pid == 0)
        {
            ls(token2);
            exit(0);
        }
    }
    else if (!strncmp(token, "ronly", 6))
    {
        if (pipe(pfds) == -1)
        {
            perror("pipe rip\n");
            exit(1);
        }
        pid = fork();
        if (pid == 0)
        {
            ronly(token2);
            exit(0);
        }
    }
    else if (!strcmp(token, "add"))
    {
        add(token2);
    }
    else if (!strcmp(token, "chmod"))
    {
        char *name = strtok(NULL, " ");
        int p = atoi(token2);
        chmod(name, p);
    }
    else if (!strncmp(token, "search", 6))
    {
        if (pipe(pfds) == -1)
        {
            perror("pipe rip\n");
            exit(1);
        }
        pid = fork();
        if (pid == 0)
        {
            search(token2);
            exit(0);
        }
    }
    if (pid != -123)
    {
        close(pfds[1]);
        char *buf2 = buf;
        int len = 0;
        while (read(pfds[0], buf2, 1) > 0)
        {
            buf2 += 1;
            len += 1;
        }
        buf[len] = '\0';
        wait(NULL);
        printf("%s", buf);
        fflush(stdout);
    }
}
int main(void)
{
    memset(buf, 0, 1000);
    int n;
    scanf("%d", &n);
    char c = getchar(); //for fgets
    fflush(stdin);
    char cmd[200];
    for (int i = 0; i < n; i++)
    {
        gets(cmd);
        add_handler(cmd);
    }
    scanf("%d", &n);
    c = getchar();
    fflush(stdin);
    for (int i = 0; i < n; i++)
    {
        gets(cmd);
        fflush(stdin);
        cmdhandler(cmd);
    }
}