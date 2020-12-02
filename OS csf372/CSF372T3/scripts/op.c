#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv){
	if(argc > 3){
		int n1= atoi(argv[1]);
		int n2 = atoi(argv[2]);
		char op = argv[3][0];
		switch(op){
			case '+':
				printf("%d + %d = %d",n1,n2,n1+n2);
				break;
			case '-':
				printf("%d - %d = %d",n1,n2,n1-n2);
				break;
			case '*': //shell requires you to escape this: \*
				printf("%d * %d = %d",n1,n2,n1*n2);
				break;
			case '/':
				printf("%d / %d = %d",n1,n2,n1/n2);
				break;
			default:
				break;
		} 
	}
	return 0;
}
