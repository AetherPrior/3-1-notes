#include<sched.h>
#include<stdio.h>
#include<linux/sched.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char **argv)
{
	int policy;
	struct sched_param sp;
	policy = 
		(argv[1][0] == 'r')?SCHED_RR:
		(argv[1][0] == 'f')?SCHED_FIFO:
		(argv[1][0] == 'b')?SCHED_BATCH:
		(argv[1][0] == 'i')?SCHED_IDLE:
		SCHED_OTHER;
	sp.sched_priority = atoi(argv[2]);

	if(sched_setscheduler(atoi(argv[3]), policy, &sp) == -1){
		exit(-1);
	}
	exit(0);
		

}
