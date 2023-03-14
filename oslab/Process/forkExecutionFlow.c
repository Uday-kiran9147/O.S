#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("\nstep 1 ");
    // printf("\nstep 2 ");

    printf("\nstep 3");
    fork();

    return 0;
}