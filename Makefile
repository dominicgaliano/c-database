main: main.c
	gcc main.c -o main.o -Wall -Wextra -pedantic -std=c11 -g -O3

run: main.o
	./main.o
