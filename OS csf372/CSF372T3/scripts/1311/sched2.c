#include<stdio.h>
#include<sched.h>

int main(void){
	int policy;
	struct timespec ts;
	
	int pmin, pmax, priority = 36;

	struct sched_param sp , sp2;

	pmin = sched_get_priority_min(SCHED_FIFO);
	pmax =  sched_get_priority_max(SCHED_FIFO);

	int initial_priority; sched_getparam(0,&sp);

	printf("Priority before resetting = %d\n", sp.sched_priority);
	if(priority >= pmin && priority <= pmax){
		sp.sched_priority = priority;
	}
	else{
		sp.sched_priority = pmin;
	}
	sched_setparam(0,&sp); // pid, sched_param
	sched_getparam(0,&sp2);//check if it has been reflected, but SCHED_FIFO doesn't allow priorities other than 0.
        //Default policy is SCHED_OTHER
	printf("Priority after resetting = %d\n", sp2.sched_priority);
}
