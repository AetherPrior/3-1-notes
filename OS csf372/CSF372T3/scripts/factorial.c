#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv){
	if(argc > 1){
		int n = atoi(argv[1]);
		long long res =1;
		if(n > 1){
		for(int i =2; i <=n; i++){
			res*=i;
		}
		}
		printf("%lld" ,res);
	}
	return 0;
}
