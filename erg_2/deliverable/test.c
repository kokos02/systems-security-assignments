#include <stdio.h>
#include <unistd.h>
 
int main()
{
    int id,i;
     
    printf("\nStart of main(fork not yet called)\n\n");
     
    id=fork();

    if(id>0)
    {
        /*parent process*/
        printf("Parent section with pid=%d\n",getpid());
    }
    else if(id==0)
    {
        /*child process*/
        printf("\nChild section with child pid=%d\n",getpid());
        printf("Child section with parent pid=%d\n",getppid());
    }
    else
    {
        /*fork creation faile*/
        printf("\nfork failure\n");
    }
     
    printf("Printing the numbers from 1 to 5\n");
    for(i=1; i<=5; i++)
        printf("%d ",i);
    printf("\n");
    printf("End of main...\n");
 
    return 0;
}