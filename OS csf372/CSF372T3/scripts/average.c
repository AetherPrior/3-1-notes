#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv){
	if(argc > 1){
		int av = atoi(argv[1]);
		for(int i = 1; i < argc; i++){
			int k = atoi(argv[i]);
			av = (av*(i-1)+k)/i;
		}
	return av;		
	}
}

