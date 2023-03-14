#include  <stdio.h>
#include  <sys/types.h>
#include  <unistd.h>

int  main()
{
    pid_t pid = fork();
    if (pid == 0)   // child proccess id is always = 0 .
        printf("Child process created\n");
    else
        printf("Parent process created\n");
    return 0;
}

//Output

//Parent process created
//Child process created
