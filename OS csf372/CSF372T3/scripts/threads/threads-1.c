#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5
void *printHello(void *arg)
{
    //same function signature void* can be used for any argument
    long tid = (long)arg;
    printf("Hello world from thread number #%d\n", tid);
    pthread_exit(NULL); //optional, you can return whatever too
}
int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("In main thread, creating threads #%ld\n", t);
        rc = pthread_create(&threads[t], /*pointer to p_thread*/
                            NULL,        /*attribute = NULL*/
                            printHello,  /*function to execute in a thread*/
                            (void *)t /*argument to the function*/);
        if (rc)
        {
            printf("Error in creating thread #%ld: %d\n", t, rc);
            exit(1);
        }
        pthread_join(threads[t], NULL); //comment this out for asynchronous behavior
    }
    pthread_exit(NULL); //optional, you can also return
}