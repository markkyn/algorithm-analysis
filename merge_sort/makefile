PROJ_NAME = merge_sort

CC = gcc

CC_FLAGS =  -Wall 	\
			-O3 	\
			-std=c99

main: main.o
	$(CC) $(CC_FLAGS) main.o -o main

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c

clean:
	rm -f *.o main