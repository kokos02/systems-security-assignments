#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>
#include <stdlib.h>
#include <string.h>

#define SYSTEM_CALLS_NUMBER 357
#define BLACKLIST_SYSTEM_CALLS_NUMBER 8
#define SYSTEM_CALL_LENGTH 20
#define BYTES_FOR_SYS_CALL_STRING 50
#define BYTES_FOR_WHOLE_LINE_STRING 70
#define NO_SYS_CALL_NUM_0 222
#define NO_SYS_CALL_NUM_1 223
#define NO_SYS_CALL_NUM_2 251
#define NO_SYS_CALL_NUM_3 285
#define NO_SYS_CALL_NUM_4 355
#define SINGLE_DIGIT_NUM_SYS_CALL_NUM_ELIMINATOR 3
#define TWO_DIGIT_NUM_SYS_CALL_NUM_ELIMINATOR 4
#define THREE_DIGIT_NUM_SYS_CALL_NUM_ELIMINATOR 5
#define GETPID_NUMBER 20

void init_system_call_table(char system_call_table[SYSTEM_CALLS_NUMBER][SYSTEM_CALL_LENGTH])
{

    FILE *system_calls;
    char *line = malloc(BYTES_FOR_SYS_CALL_STRING * sizeof(char)); // we allocate just enough bytes for our string
    int sys_count;

    system_calls = fopen("/usr/include/i386-linux-gnu/asm/unistd_32.h", "r");

    //we move to the first actual system call
    fgets(line, BYTES_FOR_WHOLE_LINE_STRING, system_calls);
    fgets(line, BYTES_FOR_WHOLE_LINE_STRING, system_calls);
    fgets(line, BYTES_FOR_WHOLE_LINE_STRING, system_calls);
    fgets(line, BYTES_FOR_WHOLE_LINE_STRING, system_calls);

    for (sys_count = 0; sys_count < SYSTEM_CALLS_NUMBER; sys_count++)
    {
        if (sys_count == NO_SYS_CALL_NUM_0 || sys_count == NO_SYS_CALL_NUM_1 || sys_count == NO_SYS_CALL_NUM_2 || sys_count == NO_SYS_CALL_NUM_3 || sys_count == NO_SYS_CALL_NUM_4) // numbers with no assigned system call
        {
            continue;
        }

        line += 13; // this way we wliminate #define __NR_

        //eliminate the number next to the system call depending on the digits each time
        if (sys_count < 10)
        {
            line[strlen(line) - SINGLE_DIGIT_NUM_SYS_CALL_NUM_ELIMINATOR] = '\0';
        }
        else if (sys_count < 100)
        {
            line[strlen(line) - TWO_DIGIT_NUM_SYS_CALL_NUM_ELIMINATOR] = '\0';
        }
        else
        {
            line[strlen(line) - THREE_DIGIT_NUM_SYS_CALL_NUM_ELIMINATOR] = '\0';
        }

        // insert the system call to our system call table
        strcpy(system_call_table[sys_count], line);

        // clear and reallocate the line
        memset(line, 0, strlen(line));
        line = malloc(BYTES_FOR_SYS_CALL_STRING * sizeof(char));

        // go to next line
        fgets(line, BYTES_FOR_WHOLE_LINE_STRING, system_calls);
    }

    fclose(system_calls);
}

void init_blacklist(char blacklist[BLACKLIST_SYSTEM_CALLS_NUMBER][SYSTEM_CALL_LENGTH])
{

    FILE *blacklist_file;
    blacklist_file = fopen("blacklist.txt", "r");
    int index = 0;
    char *line = malloc(BYTES_FOR_SYS_CALL_STRING * sizeof(char));

    while (fgets(line, SYSTEM_CALL_LENGTH, blacklist_file) != NULL)
    {

        //if the system call is not the last in blacklist we eliminate the '\n' character
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 2] = '\0';
        }

        // insert the blacklisted system call to our blacklist table
        strcpy(blacklist[index], line);
        index++;

        // clear and reallocate the line
        memset(line, 0, strlen(line));
        line = malloc(BYTES_FOR_SYS_CALL_STRING * sizeof(char));
    }
}

int check_blacklist(long sys_call_number, char blacklist[BLACKLIST_SYSTEM_CALLS_NUMBER][SYSTEM_CALL_LENGTH], char system_call_table[SYSTEM_CALLS_NUMBER][SYSTEM_CALL_LENGTH])
{

    int blacklist_iterator;

    //we find the sys_call_number in the system call table and if it exists also in the blacklist table we retun 1 otherwise 0
    for (blacklist_iterator = 0; blacklist_iterator < BLACKLIST_SYSTEM_CALLS_NUMBER; blacklist_iterator++)
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
    char system_call_table[SYSTEM_CALLS_NUMBER][SYSTEM_CALL_LENGTH] = {};
    char blacklist[BLACKLIST_SYSTEM_CALLS_NUMBER][SYSTEM_CALL_LENGTH] = {};
    pid_t pid;
    int wait_status;
    int enter_syscall = 1;
    long orig_eax;
    int prohibited_calls_counter = 0;
    int total_calls_counter = 0;
    int unique_calls_counter = 0;
    int system_calls_appearance[SYSTEM_CALLS_NUMBER] = {0};
    int system_call_iterator;

    //populate system call and blacklist table
    init_system_call_table(system_call_table);
    init_blacklist(blacklist);

    pid = fork();

    if (pid == 0)
    {
        ptrace(PTRACE_TRACEME, NULL, NULL, NULL); // indicate that this process should
        //be traced by it's parent trace MEEEE!!!!
        execl("./test", "test", NULL); //it will trace the execution of the test file
    }
    else if (pid > 0)
    {
        wait(&wait_status); //suspends execution of the calling thread
                            //until a child has changed state
        while (1)
        {
            orig_eax = ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_EAX, NULL); // we get the current system call number

            //if the current system call is in the blacklist
            if (check_blacklist(orig_eax, blacklist, system_call_table))
            {
                printf("\nblacklisted call: %ld changed to getpid\n\n", orig_eax);
                ptrace(PTRACE_POKEUSER, pid, 4 * ORIG_EAX, GETPID_NUMBER); // we change it to getpid
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

            //restart stopped tracee but arrange to stop in the next system call
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

    //we check if each system call was executed but count it only once
    for (system_call_iterator = 0; system_call_iterator < SYSTEM_CALLS_NUMBER; system_call_iterator++)
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