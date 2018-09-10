CC= g++
CFLAGS= -Wextra -Wvla -Wall -std=c++14 -g

all: ex2

ex2:  Item.o ex2.o
	$(CC) $(CFLAGS) ex2.o -o ex2

ex2.o: ikea.cpp ikea.h Item.h Candy.h Furniture.h Fabric.h MoviesAndBooks.h Kitchenware.h TablesAndChairs.h
	$(CC) -c $(CFLAGS) ikea.cpp -o ex2.o

Item.o: Item.h
	$(CC) -c $(CFLAGS) Item.cpp -o Item.o

clean:
	-rm -f *.o ex2