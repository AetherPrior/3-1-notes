#include<stdio.h>
#include<unistd.h>
int main(void){
    
    fork(); //returns pid_t
    //parent - fork returns pid of child
    //child - fork returns 0
    //error - fork returns negative (eg: no more mem)
    printf("Hello\n");
    return 0;
}

