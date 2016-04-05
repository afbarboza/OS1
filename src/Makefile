all:
	gcc main.c busstop.c bus.c list.c passenger.c -o prog -g -pthread

allw:
	gcc main.c busstop.c bus.c list.c passenger.c -o prog -g -pthread -Wall

run:
	./prog 5 2 40 4

valgrind:
	valgrind --leak-check=full ./prog 5 2 40 4

gdb:
	gdb --silent ./prog

clear:
	rm ./prog


