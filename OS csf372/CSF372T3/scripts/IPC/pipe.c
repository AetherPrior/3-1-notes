#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(void){
int pfds[2];
char buf[1000];
pipe(pfds);
if(!fork()){
 for(int i = 0; i < 10; i++)write(pfds[1],"child",5);
}
else{
for(int i = 0; i < 1; i++)write(pfds[1],"parent",6);
read(pfds[0],buf,500);
printf("%s",buf);
wait(NULL);
}
return 0;
}
