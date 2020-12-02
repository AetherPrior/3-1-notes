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
void ls(char *dirname)
{
    for (int i = 0; i <= size; i++)
    {
        if (dirname != NULL && strcmp(dirname, "/"))
        {
            char newdir[100];
            char *nextdir = newdir + 1;
            strcpy(nextdir, dirname);
            newdir[0] = '/';
            newdir[strlen(newdir) + 1] = '\0';
            newdir[strlen(newdir)] = '/';
            if (strstr(filarr[i].name, newdir) != NULL)
            {
                printf("%s\n", filarr[i].name);
                fflush(stdout);
            }
        }
        else
        {
            printf("%s\n", filarr[i].name);
            fflush(stdout);
        }
    }
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
                printf("%s\n", tok.name);
            }
        }
    }
}
void search(char *name)
{
    for (int i = 0; i <= size; i++)
    {
        if (strstr(filarr[i].name, name) != NULL)
        {
            printf("%s\n", filarr[i].name);
        }
    }
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
    strncpy(filarr[size].permission, perms, 3);
    strcpy(filarr[size].name, filename);
}
void add_handler(char *cmd)
{
    char *token = strtok(cmd, " "), *token2 = strtok(NULL, " ");
    //token2[strlen(token2) - 1] = '\0';
    add_entry(token, token2);
}
void cmdhandler(char *cmd)
{
    char *token = strtok(cmd, " ");
    char *token2 = strtok(NULL, " ");
    /*
        if (token2 != NULL && strcmp(token, "chmod"))
        {
            token2[strlen(token2) - 1] = '\0';
        }
        */
    if (!strncmp(token, "ls", 2))
    {
        ls(token2);
    }
    else if (!strncmp(token, "ronly", 6))
    {
        ronly(token2);
    }
    else if (!strcmp(token, "add"))
    {
        add(token2);
    }
    else if (!strcmp(token, "chmod"))
    {
        char *name = strtok(NULL, " ");
        // name[strlen(name) - 1] = '\0';
        int p = atoi(token2);
        chmod(name, p);
    }
    else if (!strncmp(token, "search", 6))
    {
        search(token2);
    }
}
int main(void)
{
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
        cmdhandler(cmd);
    }
}