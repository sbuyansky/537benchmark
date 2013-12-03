537benchmark: main.o
	gcc -o 537benchmark main.o

main.o: main.c
	gcc -c main.c -Wall -pedantic

clean:
	rm -rf *.o *.txt
	rm 537benchmark

debug:
	gcc -c main.c -Wall -pedantic -ggdb
	gcc -o debug537benchmark main.o -ggdb
