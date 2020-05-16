all: inject test

test: test.o 
	gcc test.o -o test

inject: inject.o 
	gcc inject.o -o inject

test.o: test.c
	gcc -c test.c

inject.o: inject.c
	gcc -c inject.c

clean:
	rm *.o test inject

run:
	./inject

run_test:
	./test

