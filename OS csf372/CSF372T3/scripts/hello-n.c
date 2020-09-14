#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv){
	if(argc != 1){
		int n = atoi(argv[1]);
		printf("n: %d\n",n);
		for(int i= 0; i < n; i++){
			printf("Hello, World!\n");
		}
		return n;
	}
}
