main: main.o ports.o
	gcc -Wall main.o ports.o -o main
main.o: main.c ports.h
	gcc -Wall main.c -c
ports.o: ports.c ports.h
	gcc -Wall ports.c -c
clear:
	rm *.o
