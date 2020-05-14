#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid = fork();

    if (pid == 0)
    {
        printf("\nHello from Child!\n");
    }

    // parent process because return value non-zero.
    else
    {

        printf("Hello from Parent!\n");
    }

    pid = fork();

     if (pid == 0)
    {
        printf("\nHeyyyyy I'm the child Child!\n");
    }

    // parent process because return value non-zero.
    else
    {

        printf("Hahahaha it's Parent again\n");
    }

     pid = fork();

     if (pid == 0)
    {
        printf("\nChildddddd!\n");
    }

    // parent process because return value non-zero.
    else
    {

        printf("Only PARENT!!!! survives after injection\n");
    }

    return 0;
}