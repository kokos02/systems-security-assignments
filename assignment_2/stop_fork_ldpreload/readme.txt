
Test.c: simple fork representation printing the pids of the parent and the child. 

inject.c: My fork implementation which returns -1 which is the fork function error code.

Makefile: Compiles the test.c file, the inject shared libary and has the functionality
make clean to leave just the important files after making and make run which runs the 
ld_preload injecting the shared library and thus resulting in fork failure.