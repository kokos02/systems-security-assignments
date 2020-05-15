#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/ptrace.h>

int main(int argc, char const *argv[])
{
	pid_t pid = fork();
	if ( pid == 0)
	{
		printf("Child says hi: %d!\n", getpid());
	}
	else
	{
		printf("Parent says hi: %d!\n", getpid());
	}

	pid_t pid2 = fork();
	if (pid2 == 0)
	{
		printf("Second child says hi: %d!\n", getpid());
	}
	else
	{
		printf("Second parent says hi: %d!\n", getpid());
	}

	waitpid(0,0,0);

	
	return 0;
}