#include<unistd.h>
#include<sys/wait.h>
int main(void){
int pid = fork();
if(pid == 0){
sleep(100);
}
else{
wait(NULL);
}
}
