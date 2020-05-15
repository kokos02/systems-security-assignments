/* "Hint" file path: /usr/include/i386-linux-gnu/asm/unistd_32.h */

#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <i386-linux-gnu/sys/reg.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>


int inblacklist(int idex){
    FILE *list;

    list = fopen("/usr/include/i386-linux-gnu/asm/unistd_32.h", "r");

    int i = 1, buf, check;
    char table[400][400] ;
    char * tab = malloc(100);
    char * command = malloc(100);
    
    //initialize
    fgets(tab, 1000, list);
    
    fgets(tab, 1000, list);
    
    fgets(tab, 1000, list);
    
    fgets(tab, 1000, list);
    
    sscanf(tab, "#define %s", command);
    
    command = command + 5;
    //printf("command-> %s\n",command);
    //printf("----------\n");
    strcpy(table[0], command);
    for(i = 1; i <= 356; i++){
        if(i == 222 || i == 223 || i == 251|| i == 285|| i == 355){
            continue;
        }
        else{
            fgets(tab, 1000, list);
            sscanf(tab, "#define %s", command);
            command = command + 5;
            strcpy(table[i], command);
            printf("--->%s\n",table[i]);
            printf("----------\n");
        }
    }
    

    fclose(list);    
    
    FILE* blacklist;
    int bufferLength = 255;
    char buffer[bufferLength];

    blacklist = fopen("blacklist.txt", "r");

    while(fgets(buffer, bufferLength, blacklist) != NULL) {
        buffer[strlen(buffer) - 2] = '\0';
        if(strcmp(table[idex], buffer) == 0){
            return 1;
        }
    }

    fclose(blacklist);

    return 0;
}


int main(){ 

	pid_t child;
    long orig_eax, syscall;
    int i, wait_status, prohibited_calls, unique_calls, total_calls, enter_syscall;
    int system_calls[357];
    syscall = 13;
    prohibited_calls = 0;
    unique_calls = 0;
    total_calls = 0;
    enter_syscall = 1;

    for (i = 0; i < 357; ++i)
    {
    	system_calls[i] = 0;
    }

    child = fork();

    /* Child process: */
    if(child == 0) {
    	/* Tracing the child process: */
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        /* Running the test executable: */
        execl("./test", "test", NULL);
    }

    else {

    	wait(&wait_status);

    	while(1){
    		
	        /* Looking which system call the program is making: */
	        orig_eax = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_EAX, NULL);
	        /* printf("The child made a system call: %ld.\n", orig_eax); */

	        /* SHOULD BE: if in blacklist, but for now is if is clone: */
	        if (inblacklist((int) orig_eax)){
                printf("The child tried making a system call: %ld.\n", orig_eax);

	        	/* Changing the system call number for time system call number: */
	        	ptrace(PTRACE_POKEUSER, child, 4 * ORIG_EAX, syscall);

	        	/* Checking if i did it: */
	        	orig_eax = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_EAX, NULL);
	        	printf("I changed the system call to: %ld.\n", orig_eax);

	        	prohibited_calls++;
	        }
	        else{
                /* Entering the system call */
	        	if (enter_syscall == 1)
	        	{
	        		system_calls[orig_eax]++;
	        		total_calls++;
	        		enter_syscall = 0;
	        	}
                /* Exiting the system call */
	        	else{
	        		enter_syscall = 1;
	        	}
	        }


	        /* Continuing: */
	        ptrace(PTRACE_SYSCALL, child, NULL, NULL);

	        wait(&wait_status);

	        /* Stop loop if exit: */
	        if(WIFEXITED(wait_status)){
	            break;
	        }
	    }
    }

    printf("\nSTATISTICS:\n");
    printf("The total number of system calls that were prohibited:      %d.\n", prohibited_calls);
    printf("The total number of system calls that were executed:        %d.\n", total_calls);
    for (i = 0; i < 357; ++i)
    {
    	if (system_calls[i] > 0)
    	{
    		unique_calls++;
    	}
    }
    printf("The total number of unique system calls that were executed: %d.\n", unique_calls - 1);


    return 0;
}