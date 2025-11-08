all: programa

run: programa
	valgrind --leak-check=full ./programa

programa: main.o funciones.o
	g++ -g -o programa main.o funciones.o

main.o: main.cpp includes.h globales.h funciones.h
	g++ -c main.cpp

funciones.o: funciones.cpp funciones.h
	g++ -c funciones.cpp

clean:
	rm -f programa *.o