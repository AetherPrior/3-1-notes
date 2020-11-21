#include<unistd.h>
#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>

int main(void){
	int fd=1;
	char *mapaddr;
	int len = getpagesize();//similar to sysconf
	printf("Page size: %d\n",len);
	
	int prot = PROT_WRITE | PROT_READ;//you can't execute, only read/write
	if((fd = open("test.txt", O_RDWR |O_CREAT, 0666)) <0)
		perror("Error in open");
	mapaddr = (char*)mmap((void*)0/*we passed NULL*/,len,prot, MAP_SHARED, fd, 0);
	if(mapaddr == MAP_FAILED)
			perror("Error in mmap\n");
	printf("mmap succeeded\n");
	printf("Content: %s\n",mapaddr);
	mapaddr = "Operating systems";
	printf("Content: %s\n",mapaddr);

}
//read man mmap, getpagesize, open, write
