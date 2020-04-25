
all: testWithMyFork inject

testWithMyFork: test.o inject.o
	gcc test.o -o testWithMyFork

inject: inject.o 
	gcc -shared -fPIC inject.o -o inject.so

test.o: test.c
	gcc -c test.c

inject.o: inject.c
	gcc -c inject.c

clean:
	rm *.o testWithMyFork inject.so
