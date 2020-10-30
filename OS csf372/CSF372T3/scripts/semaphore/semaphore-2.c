#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define BUFF_SIZE 5
#define NP 3
#define NC 3 
#define NITERS 4

typedef struct {
	int buf[BUFF_SIZE], in, out;
	sem_t full,empty;
	pthread_mutex_t mutex;

}sbuf_t;
sbuf_t shared;

void *Producer(void *arg){
	int i,item;
	long index = (long)(arg);
	for(i = 0; i < NITERS; i++){
		item = i; // Producing

		sem_wait(&shared.empty); //empty == 0 -> everything is full
		pthread_mutex_lock(&shared.mutex);
		
		shared.buf[shared.in] = item;
		shared.in = (shared.in+1)%BUFF_SIZE;
		printf("Producer %d has produced item %d\n", index, item);
	
		pthread_mutex_unlock(&shared.mutex);	
		sem_post(&shared.full); //incrememnt full
		
		if(i%2 == 1)
			sleep(1);
	}	
}
void *Consumer(void *arg){
	int i, item;
	long index = (long)(arg);
	for(i=0; i< NITERS; i++){
		sem_wait(&shared.full);//full = 0 -> everything is empty
		pthread_mutex_lock(&shared.mutex);
	
		item = shared.buf[shared.out];
		shared.out = (shared.out+1)%BUFF_SIZE;
		printf("Consumer %d has consumed item %d\n", index, item);
	
		pthread_mutex_unlock(&shared.mutex);	
		sem_post(&shared.empty); //increment empty
		if(i%2 == 0)
			sleep(1);

	}
}
int main(void){
	pthread_t iDP, iDC;
	long index;

	sem_init(&shared.empty, 0, BUFF_SIZE);
	sem_init(&shared.full, 0, 0);

	pthread_mutex_init(&shared.mutex, NULL);

	for(index = 0; index < NP; index++)
	{
		pthread_create(&iDP, NULL, Producer, (void*)index);
	}
	for(index = 0; index < NC; index++)
	{
		pthread_create(&iDC,NULL, Consumer, (void*)index);
	}
    pthread_exit(0); //refer man page, it is necessary in main()
}
