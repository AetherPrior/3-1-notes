    #include <stdio.h> 
    #include <stdlib.h> 
    #include <string.h>
    #include <unistd.h>
    #include <sys/wait.h>
     
    void foo()
    {
    	printf("bar\n");
    	int pid = fork();
    	if(!pid)
    	{
    	    printf("%d\n", pid);
    	    printf("child\n");
    	}
    	else
    	{
    	    wait(NULL);
    	    printf("%d\n", pid);
            printf("parent\n");
    	}
    }
     
    int main()
    {
        foo();
    	return 0;
    }
