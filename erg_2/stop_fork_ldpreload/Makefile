
all: test_my_fork inject.so

test_my_fork: test.o 
	gcc test.o -o test_my_fork

inject.so: inject.o 
	gcc -shared -fPIC inject.o -o inject.so

test.o: test.c
	gcc -c test.c

inject.o: inject.c
	gcc -c inject.c

clean:
	rm *.o test_my_fork inject.so

run:
	LD_PRELOAD=./inject.so ./test_my_fork

run_no_ld_preload:
	./test_my_fork

