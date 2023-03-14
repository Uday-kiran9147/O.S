#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int args, char *argv[])
{
    int pid = fork();
    int n;
    if (pid == 0) // child id=0
    {             // id of child process is always gonna be 0
        n = 1;
    }
    else
        printf("\nhello world from parent id : %d\n", pid);
    {
        n = 6;
    }
    if (pid != 0)
    {
        // wait();
    }
    for (int i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        fflush(stdout);
    }
    // printf("\n");
    return 0;
}
