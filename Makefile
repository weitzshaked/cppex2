CC= g++
CFLAGS= -Wextra -Wvla -Wall -std=c++14 -g

all: ex2

ex2:  ex2.o
	$(CC) $(CFLAGS) ex2.o -o ex2

ex2.o: ikea.cpp ikea.h Item.h Cloth.h Candy.h Furniture.h Fabric.h MoviesAndBooks.h Kitchenware.h TablesAndChairs.h
	$(CC) -c $(CFLAGS) ikea.cpp Item.cpp -o ex2.o

clean:
	-rm -f *.o ex2