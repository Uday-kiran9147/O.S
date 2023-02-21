#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid, pid1;
	// int i =8;
	char buf[100];
	printf("Initial Id: %d\n", getpid());
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork failed");
	}
	else if (pid == 0)
	{
		pid1 = getpid();
		printf("Child : pid = %d \n", pid);
		printf("Child : pid1 = %d \n", pid1);
		for (int i = 1; i <= 500; i++)
		{
			sprintf(buf, "This line is from pid %d, value = %d\n", pid1, i);
			write(1, buf, strlen(buf));
		}
		printf("Child : pid1 = %d \n", getppid());
	}
	else
	{
		pid1 = getpid();
		printf("Parent: pid = %d \n", pid);
		printf("Parent: pid1 = %d \n", pid1);
		for (int i = 1; i <= 50; i++)
		{
			sprintf(buf, "This line is from pid %d, value = %d, parent = %d\n", pid1, i, getppid());
			write(1, buf, strlen(buf));
		}
		exit(0); // return 0;
	}
}
// Output

// Parent process created
// Child process created
