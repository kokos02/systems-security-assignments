stop_fork_ldpreload:

Test.c: simple fork representation printing the pids of the parent and the child. 

inject.c: My fork implementation which returns -1 which is the fork function error code.

Makefile: Compiles the test.c file, the inject shared libary and has the functionality,
make clean to leave just the important files after making and make run which runs the 
ld_preload injecting the shared library and thus resulting in fork failure.

stop_fork_ptrace:

Test.c: simple fork representation printing the pids of the parent and the child.

inject.c: it calls fork and make test the tracee, when it encounters clone system call whicj is the same as fork
it changes the eax register which holds the system call number to getpid and thus it avoid the execution of the fork.

blacklist_ptrace:

Same functionality as the above but this time we have a blacklist of prohibited system calls to 
avoid except for fork.

secret sharing:

We use the command make to compile the files and make clean to clean the useles 
files after execution.

split: The user inputs the password (we limit it in a range between 4 to 8 digits
to avoid overflows), the dev/Urandom generates random coeficients that are limited to 255 
(we could use dev/random but it's too slow and has more or less the same result) 
and the last and second to last to 20 to avoid overflows, then we calculate the polyonim for each 
user 1 to 10 and write it with it's index to a file.

join: we get the values with their indexes from the file, construct the augmented matrix in
a form suitable for gauss elimination and then apply gauss elimination to find the password.


