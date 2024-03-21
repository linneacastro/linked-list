main: main.o functions.o main.h
	gcc -g -o main main.o functions.o
main.o: main.c main.h
	gcc -g -c main.c
functions.o: functions.c main.h
	gcc -g -c functions.c
clean:
	rm functions.o main.o main
