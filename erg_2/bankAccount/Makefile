
all: split join

split: split.o 
	gcc split.o -lm -o split

join: join.o 
	gcc join.o -lm -o join

split.o: split.c
	gcc -c split.c

join.o: join.c
	gcc -c join.c

clean:
	rm *.o split join
