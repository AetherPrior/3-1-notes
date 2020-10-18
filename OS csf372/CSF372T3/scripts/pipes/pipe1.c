#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>
int main(void){
    //intra process communication using pipes
    int pfds[2];
    char buf[30];
    //create an ordinary pipe in linux
    
    /*
     * 0-stdin -> kb
     * 1-stdout -> display/terminal
     * 2-stderr -> display/terminal
     * pip2(pfds[2]) -> [0] ->read end
     *               -> [1] ->write end
     */
    
    if(pipe(pfds) == -1){
        perror("Error in creating pipe\n");
        exit(1);
    }
    if(!fork())
    {
        close(pfds[0]); //a matter of safety
        for(long long i = 0; i< 1000000000; i++);
        write(pfds[1],"tesT",5);
        printf("Child exiting\n");
        exit(0);
    }
    else{
        close(pfds[1]); //also a matter of safetys
        read(pfds[0],buf,5); //blocks the execution, until something is read
        printf("parent: %s\n",buf);
        wait(NULL); //waiting for child to end, but after stuff is done, since child can be made to run very long
    }
    /*
    printf("Writing to file descriptor #%d\n",pfds[1]);
    write(pfds[1], "test", 5); //nullchar
    printf("Reading from file descriptor #%d\n",pfds[0]);
    read(pfds[0], buf, 5);
    printf("We have read: \"%s\"\n", buf);
    */
    return 0;
}
