#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>

sem_t sem;
int counter; //global variables are initialized to 0
void *handler(void *ptr)
{
    int x = *((int*)ptr);
    printf("Thread %d is waiting to enter the critical section\n",x);
    sem_wait(&sem); //value > 0? --value: wait();
    //Critical section begins
    printf("Thread %d is now in the critical section\n",x);
    printf("Thread %d | Counter %d\n",x,counter);
    printf("Thread %d is incrementing the counter\n", x);
    counter++;
    printf("Thread %d | new value of counter is%d\n", x, counter);
    printf("Thread %d now exiting the critical section\n",x);
    //Critical section ends
    sem_post(&sem);
    pthread_exit(NULL);
    
}

int main(void){
    int i[2] = {0,1}; //just 2 int vars
    pthread_t thread_a, thread_b;
    
    sem_init(&sem, 0, 1);
    pthread_create(&thread_a, NULL, (void*)&handler, (void*)&i[0]);
    pthread_create(&thread_a, NULL, (void*)&handler, (void*)&i[1]);
    
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    
    sem_destroy(&sem);
    return 0;
}
/*
       The pshared argument indicates whether this semaphore is to be shared between the threads of a process, or between
       processes.

       If  pshared  has the value 0, then the semaphore is shared between the threads of a process, and should be located
       at some address that is visible to all threads (e.g., a global variable, or a variable  allocated  dynamically  on
       the heap).

       If pshared is nonzero, then the semaphore is shared between processes, and should be located in a region of shared
       memory (see shm_open(3), mmap(2), and shmget(2)).  (Since a child created by fork(2) inherits its parent's  memory
       mappings,  it can also access the semaphore.)  Any process that can access the shared memory region can operate on
       the semaphore using sem_post(3), sem_wait(3), and so on.

       Initializing a semaphore that has already been initialized results in undefined behavior.
*/
