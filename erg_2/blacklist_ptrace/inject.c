#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>
#include <stdlib.h>
#include <string.h>


void init_system_call_table(char system_call_table[357][20])
{

    FILE *system_calls;
    char *line = malloc(50 * sizeof(char));
    int sys_count;

    system_calls = fopen("/usr/include/i386-linux-gnu/asm/unistd_32.h", "r");

    //we move to the first actual system call
    fgets(line, 1000, system_calls);
    fgets(line, 1000, system_calls);
    fgets(line, 1000, system_calls);
    fgets(line, 1000, system_calls);

    for (sys_count = 0; sys_count < 357; sys_count++)
    {
        if (sys_count == 222 || sys_count == 223 || sys_count == 251 || sys_count == 285 || sys_count == 355)
        {
            continue;
        }
        line += 13;
        if (sys_count < 10)
        {
            line[strlen(line) - 3] = '\0';
        }
        else if (sys_count < 100)
        {
            line[strlen(line) - 4] = '\0';
        }
        else
        {
            line[strlen(line) - 5] = '\0';
        }

        //line[strlen(line) - 3] = '\0';
        strcpy(system_call_table[sys_count], line);
        //printf("line-> %s\n", system_call_table[sys_count]);
        memset(line, 0, strlen(line));
        line = malloc(50 * sizeof(char));

        fgets(line, 1000, system_calls);
    }
    fclose(system_calls);
}

void init_blacklist(char blacklist[8][20])
{

    FILE *blacklist_file;
    blacklist_file = fopen("blacklist.txt", "r");
    int index = 0;
    char *line = malloc(50 * sizeof(char));

    while (fgets(line, 20, blacklist_file) != NULL)
    {

        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 2] = '\0';
        }

        strcpy(blacklist[index], line);
        index++;
        memset(line, 0, strlen(line));
        line = malloc(50 * sizeof(char));
    }
}

int check_blacklist(long sys_call_number, char blacklist[8][20], char system_call_table[357][20])
{

    int blacklist_iterator;
    for (blacklist_iterator = 0; blacklist_iterator < 8; blacklist_iterator++)
    {
        if (!strcmp(system_call_table[sys_call_number], blacklist[blacklist_iterator]))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    char system_call_table[357][20] = {};
    char blacklist[8][20] = {};
    pid_t pid;
    int wait_status;
    int enter_syscall = 1;
    long orig_eax;
    int injected_system_call = 20; //getpid
    int prohibited_calls_counter = 0;
    int total_calls_counter = 0;
    int unique_calls_counter = 0;
    int system_calls_appearance[357]={0};
    int system_call_iterator;

    init_system_call_table(system_call_table);
    init_blacklist(blacklist);

    pid = fork();

    if (pid == 0)
    {
        ptrace(PTRACE_TRACEME, NULL, NULL, NULL); // indice that this process should
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


            if (check_blacklist((int)orig_eax, blacklist, system_call_table))
            {
                printf("blacklisted call: %ld.\n", orig_eax);
                ptrace(PTRACE_POKEUSER, pid, 4 * ORIG_EAX, injected_system_call);
                prohibited_calls_counter++;
            }

            if (enter_syscall == 1)
            {
                total_calls_counter++;
                enter_syscall = 0;
                system_calls_appearance[orig_eax]++;
            }
            else
            {
                enter_syscall = 1;
            }
            ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
            wait(&wait_status);

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

    for (system_call_iterator = 0; system_call_iterator < 357; system_call_iterator++)
    {
    	if (system_calls_appearance[system_call_iterator] > 0)
    	{
    		unique_calls_counter++;
    	}
    }

    printf("total system calls executed: %d\n", total_calls_counter);
    printf("unique system calls executed: %d\n", unique_calls_counter);
    printf("prohibited system calls executed: %d\n", prohibited_calls_counter);
    return 0;
}