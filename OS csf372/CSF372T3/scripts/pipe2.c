#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>
int main(void){
    pid_t pid;
    int pfds[2];
    int s;
    pipe(pfds);
    pid = fork();
    if(pid == -1){
        perror("Error in creating process\n");
    }
    else if(pid == 0){
        dup2(pfds[1],1); //1->stdout
        close(pfds[0]);
        close(pfds[1]);
        if(execlp("ls", "ls",NULL) == -1){ //write to pipe intead now
                                            // although pipe is closed, the fd #1 isn't
            perror("Error executing ls\n"); 
        }
    }
    else{
            if(fork() == 0){
                dup2(pfds[0],0);
                close(pfds[1]);
                close(pfds[0]);
                if(execlp("wc","wc", "-l",NULL) == -1){ //read from pipe intead now 
                                                        // write to stdout, since stdout isn't mappeds
                    perror("Error in execing wc\n"); 
                }
            }
            else{
                close(pfds[0]);
                close(pfds[1]);
                wait(&s);
                wait(&s);
            }
        }
     return 0;
}
