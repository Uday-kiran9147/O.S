#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int args, char *argv[])
{
    int pid = fork();
    // wait(pid);
    if (pid == 0) //child id=0
    {             // id of child process is always gonna be 0

        printf("hello world from child id : %d\n", pid);
    }
    else
    {
        printf("hello world from parent id : %d\n", pid);
    }

    return 0;
}