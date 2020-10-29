     #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<errno.h>
    #include<sys/wait.h>
    #include<unistd.h>
     
    char PERMISSIONS[8][4] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
     
    typedef struct Entry
    {
        char permission;
        char name[105];
        int parent;
    } Entry;
     
    Entry entries[100];
    int SIZE;
     
    int find(char filename[])
    {
        for(int i = 0; i <= SIZE; i++)
        {
            if(strcmp(entries[i].name, filename) == 0)
                return i;
        }
        return -1;
    }
     
    void add_entry(char filename[], char prev[], char p)
    {
        if(find(filename) != -1)
            return;
     
        SIZE += 1;
        entries[SIZE].parent = find(prev);
        entries[SIZE].permission = 4;
        strcpy(entries[SIZE].name, filename);
        if(p != -1)
            entries[SIZE].permission = p;
    }
     
    char get_permission(char perm[])
    {
        for(char i = 0; i < 8; i++)
        {
            if(strcmp(PERMISSIONS[(int)i], perm) == 0)
                return i;
        }
        return -1;
    }
     
    void add(char filename[], char permission)
    {
        char *token = strtok(filename, "/");
        char temp1[100], temp2[100];
        strcpy(temp1, "~");
        strcpy(temp2, "~");
        while(token != NULL)
        {
            strcat(temp2, "/");
            if((strcspn(token, ".") == strlen(token)) && (find(temp1) <= 0))
                strcat(temp2, "/");
            strcat(temp2, token);
            add_entry(temp2, temp1, permission);
            //printf("Adding token %s\n", temp2);
            token = strtok(NULL, "/");
            strcpy(temp1, temp2);
        }
    }
     
    void chmod(char new_perm, char filename[])
    {
        char temp[105];
        strcpy(temp, "~/");
        strcat(temp, filename);
        int entry = find(temp);
        if(new_perm < 0 || new_perm > 7)
        {
            //printf("Error in setting permission number\n");
            return;
        }
        if(entry > -1)
            entries[entry].permission = new_perm;
        //else
            //printf("Error in setting permissions\n");
    }
     
    void ls(int pfds[], char *dir_path)
    {
        if(dir_path == NULL)
        {
            for(int i = 0; i <= SIZE; i++)
            {
                char t[105];
                strcpy(t, entries[i].name);
                char *ftype = strtok(t, ".");
                ftype = strtok(NULL, ".");
                if(ftype == NULL)
                    continue;
                write(pfds[1], &entries[i].permission, 1); // Write permission to pipe
                write(pfds[1], &entries[i].name[2], 104); // Followed by the file itself
            }
        }
        else
        {
            char temp[105], t[105];
            strcpy(t, dir_path);
            strcpy(temp, "~/");
            int x = strcspn(t, ".");
            if(x < strlen(t))
                return;
            else
            {
                if(t[0] != '/')
                    strcat(temp, "/");
                x = strlen(t)-1;
                if(t[x] == '/')
                    t[x] = '\0';
                
            }
            strcat(temp, t);
            int cwd = find(temp);
            if(cwd == -1)
                return;
            for(int i = 0; i <= SIZE; i++)
            {
                if(entries[i].parent == cwd)
                {
                    char t[105];
                    strcpy(t, entries[i].name);
                    //printf("Currently parsing : %s\n", entries[i].name);
                    char *ftype = strtok(t, ".");
                    ftype = strtok(NULL, ".");
                    if(ftype == NULL)
                    {
                        ls(pfds, &entries[i].name[2]); // Recursively parse subdirs
                    }
                    else
                    {
                        write(pfds[1], &entries[i].permission, 1); // Write permission to pipe
                        write(pfds[1], &entries[i].name[2], 104); // Followed by the file itself
                    }
                }
            }
        }
        //char c = -1;
        //write(pfds[1], &c, 1); // This indicates end of the stream read from pipe
    }
     
     
    int main(void) {
        SIZE = 0;
     
        // Define root
        entries[0].permission = 4;
        strcpy(entries[0].name, "~");
        entries[0].parent = -1;
        // Root definition complete
     
        int N;
        scanf("%d", &N);
        getchar();
        for(int i = 0; i < N; i++)
        {
            char command[200];
            scanf("%[^\n]s", command);
            getchar();
            char *token = strtok(command, " ");
            char p = get_permission(token);
            token = strtok(NULL, " ");
            char file[200];
            strcpy(file, token);
            add(file, p);
        }
        scanf("%d", &N);
        getchar();
        for(int instr = 0; instr < N; instr++)
        {
            int pfds[2];
            if(pipe(pfds) == -1)
            {
                perror("Error in creating pipe. \n");
                exit(1);
            }
            char command[200];
            //scanf("%[^\n]%*c", command);
            fgets(command, 199, stdin);
            fflush(stdin);
            fflush(stdout);
            int x = strcspn(command, "\n");
            if(x < strlen(command))
                command[x] = '\0';
            //printf("Received command : %s : %d\n", command, instr);
            char *token = strtok(command, " ");
            if(strcmp(token, "ls") == 0)
            {
                char *dir_path = strtok(NULL, " ");
                if(fork() == 0)
                {
                    close(pfds[0]);
                    ls(pfds, dir_path);
                    close(pfds[1]); // If not done, then child will block on empty pipe
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    close(pfds[1]);
                    char c = -1, buf[104];
                    while((read(pfds[0], &c, 1) != 0))// && (c != -1))
                    {
                        read(pfds[0], buf, 104);
                        printf("%s\n", buf); // To get permission value, use (int)c
                        fflush(stdout);
                    }
                    close(pfds[0]);
                }
            }
            else if(strcmp(token, "ronly") == 0)
            {
                char *dir_path = strtok(NULL, " ");
                if(fork() == 0)
                {
                    close(pfds[0]);
                    ls(pfds, dir_path);
                    close(pfds[1]); // If not done, then child will block on empty pipe
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    close(pfds[1]);
                    char c = -1, buf[104];
                    while((read(pfds[0], &c, 1) != 0))// && (c != -1))
                    {
                        read(pfds[0], buf, 104);
                        if((int)c == 4)
                        {
                            printf("%s\n", buf); // To get permission value, use (int)c
                            fflush(stdout);
                        }
                    }
                    close(pfds[0]);
                }
            }
            else if(strcmp(token, "add") == 0)
            {
                char *path = strtok(NULL, " ");
                char file_path[200];
                strcpy(file_path, path);
                add(file_path, -1);
            }
            else if(strcmp(token, "chmod") == 0)
            {
                char *p = strtok(NULL, " ");
                char q[1];
                strcpy(q, p);
                char new_perm = q[0] - '0';
                char *dir_path = strtok(NULL, " ");
                char dir[200];
                strcpy(dir, dir_path);
                chmod(new_perm, dir);
            }
            else if(strcmp(token, "search") == 0)
            {
                char *dir_path = strtok(NULL, " ");
                if(fork() == 0)
                {
                    close(pfds[0]);
                    ls(pfds, NULL);
                    close(pfds[1]); // If not done, then child will block on empty pipe
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    close(pfds[1]);
                    char c = -1, buf[104];
                    while((read(pfds[0], &c, 1) != 0))// && (c != -1))
                    {
                        read(pfds[0], buf, 104);
                        if(strstr(buf, dir_path) != NULL)
                        {
                            printf("%s\n", buf); // To get permission value, use (int)c
                            fflush(stdout);
                        }
                    }
                    close(pfds[0]);
                }
            }
            else
            {
                continue;
            }
        }
        return 0;
    }
