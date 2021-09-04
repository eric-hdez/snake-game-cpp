CC = clang++ -std=c++11
CFLAGS = -Wall -g
RAYFLAGS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a

all: main

main : main.o snake.o
	$(CC) $(CFLAGS) $(RAYFLAGS) -o main main.o snake.o

main.o : snake.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp

snake.o : snake.h snake.cpp
	$(CC) $(CFLAGS) -c snake.cpp

clean : 
	rm -f main main.o snake.o
