CC=g++ $(CFLAGS)
CFLAGS=-std=c++11
winequality: main.o node.o
	$(CC) -o winequality.bin main.o node.o

main.o: main.cpp node.h
	$(CC) -c main.cpp

node.o: node.h


clean:
	rm *.o tictactoe.bin