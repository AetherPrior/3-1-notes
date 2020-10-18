#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5
int sum = 0;
void *func(void *arg)
{
    //same function signature void* can be used for any argument
    int *n = (int *)arg;
    sum += *n;
    pthread_exit(NULL); //optional, you can return whatever too
}
int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    int data[NUM_THREADS], /*errcode,*/ i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        data[i] = atoi(argv[i + 1]);
        //printf("In main thread, creating threads #%ld\n", i);
        rc = pthread_create(&threads[i], /*pointer to p_thread*/
                            NULL,        /*attribute = NULL. default.*/
                            func,        /*function to execute in a thread*/
                            (void *)&data[i] /*argument to the function*/);
        if (rc)
        {
            printf("Error in creating thread #%ld: %d\n", i, rc);
            exit(1);
        }
    }
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL); //comment this for race-condition
    }
    printf("Sum: %d\n", sum);
    pthread_exit(NULL); //optional, you can also return
}