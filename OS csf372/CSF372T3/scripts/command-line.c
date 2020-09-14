#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv){
  printf("Number of arguments: %d\n",argc-1);
  if(argc != 1){
	int n = atoi(argv[1]);
	for(int i = 0; i < n; i++){
		printf("Hello, World!\n");
	}
	for(int i  = 2; i < argc; i++){
		puts(argv[i]);
	}
  }
}
