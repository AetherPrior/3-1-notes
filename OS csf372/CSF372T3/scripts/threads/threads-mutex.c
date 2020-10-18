#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5
int sum = 0;
int inc = 5;
pthread_mutex_t mutex;

void *func(void *arg)
{
    pthread_mutex_lock(&mutex);
    /*
    * if you call this^ twice in the same thread, it may deadlock
    * if you call it in a different thread, it'll block
    */
    //Critical section
    sum += inc;
    printf("Sum: %d\n", sum);
    inc += 5;
    printf("inc: %d\n", inc);
    pthread_mutex_unlock(&mutex);
    //Critical section ends
    pthread_exit(NULL);
    //if you comment both pthread_mutex_lock and pthread_mutex_unlock you'll get inconsistencies
    //if you comment only pthread_mutex_unlock, you'll starve other threads
    //if you comment only pthread_mutex_lock, you'll do the same thing as commenting both
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int i;
    pthread_mutex_init(&mutex, NULL); //it would [destroy and] initialize a mutex
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], /*pointer to p_thread*/
                       NULL,        /*attribute = NULL. default.*/
                       func,        /*function to execute in a thread*/
                       NULL /*argument to the function*/);
    }
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL); //comment this for race-condition
    }
    pthread_exit(NULL); //optional, you can also return
}