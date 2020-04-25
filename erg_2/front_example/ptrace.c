#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

int main()
{
    pid_t pid;
    int count = 0;
    int wait_status;
    int enter_syscall = 1;

    pid = fork();

    if (pid == 0)
    {
        ptrace(PTRACE_TRACEME, NULL, NULL, NULL); // indice that this process should
        //be traced by it's parent trace MEEEE!!!!
        printf("child process\n");
        execl("/bin/date", "date", NULL); //displays date from bin/date file
    }
    else if (pid > 0)
    {
        printf("parent process\n");
        wait(&wait_status); //suspends execution of the calling thread
                            //until a child has changed state
        while (1)
        {
            if (enter_syscall == 1)
            {
                count++;
                enter_syscall = 0;
            }
            else
            {
                enter_syscall = 1;
            }
            ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
            wait(&wait_status); 

            if (WIFEXITED(wait_status))//returns true if the child terminated normally
            {
                break;
            }
        }
    }
    else
    {
        printf("fork error\n");
    }

    printf("totalsystem calls executed: %d\n", count);
    return 0;
}
