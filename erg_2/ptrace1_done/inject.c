#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>

int main()
{
    pid_t pid;
    int wait_status;
    long orig_eax;
    int injected_system_call = 20; //getpid

    pid = fork();

    if (pid == 0)
    {
        ptrace(PTRACE_TRACEME, NULL, NULL, NULL); // indicate that this process should
        //be traced by it's parent trace MEEEE!!!!
        execl("./test", "test", NULL); //displays date from bin/date file
    }
    else if (pid > 0)
    {
        wait(&wait_status); //suspends execution of the calling thread
        //until a child has changed state

        while (1)
        {

            orig_eax = ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_EAX, NULL); // we get the current system call number

            if (orig_eax == 120)
            {   //if the system call is clone(120) we stop. fork is number 2 in unistd_32 but
                //it turns out that fork calls clone for some reason

                //we change the system call number to 20 which is getpid to avoid fork execution
                // this is done on the orig_eax register which controls the system call number
                ptrace(PTRACE_POKEUSER, pid, 4 * ORIG_EAX, injected_system_call);

                //uncomment to check if orig_eax succesfully changed
                //printf("orig_eax is: %ld\n", ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_EAX, NULL));
            }

            ptrace(PTRACE_SYSCALL, pid, NULL, NULL); // restarts child until change of state
            wait(&wait_status);                      //suspends execution of the calling thread
                                                     //until a child has changed state

            if (WIFEXITED(wait_status)) //returns true if the child terminated normally
            {
                break;
            }
        }
    }
    else
    {
        printf("fork error\n");
    }

    return 0;
}
