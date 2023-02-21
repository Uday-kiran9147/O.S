#include  <stdio.h>
#include  <sys/types.h>
#include  <unistd.h>

int  main()
{
    pid_t pid, pid1;
int i =5;
	printf("Initial Id: %d\n", getpid());
	pid = fork();
	if (pid<0)
	{
	fprintf(stderr,"Fork failed");
	}
	else    if (pid == 0)
	{
	pid1 = getpid();        
	printf("Child : pid = %d \n",pid);
	printf("Child : pid1 = %d \n",pid1);
	printf("child: i value = %d\n",i);	
	printf("child: i value = %d\n",i+2);
	}
    else{
	pid1 = getpid();
        printf("Parent: pid = %d \n", pid);
        printf("Parent: pid1 = %d \n", pid1);
	printf("Parent: i value = %d\n",i);
	printf("Parent: i value = %d\n",i*2);
	i=20;
	printf("Parent: i value = %d\n",i*2);
	}
    return 0;
}

//Output

//Parent process created
//Child process created
