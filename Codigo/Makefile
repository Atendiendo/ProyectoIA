comp=g++
prog=HC+Restart

#El problema
cantNodos=10
instanciaNodos=0
cantUsuarios=5
instanciaUsuarios=0
semilla=123
restarts=10
debug=0

all: $(prog)

run: $(prog)
	valgrind --leak-check=full --show-reachable=yes \
	./$(prog) $(cantNodos) $(instanciaNodos) $(cantUsuarios) $(instanciaUsuarios) $(semilla) $(restarts) $(debug)

$(prog): main.o funciones.o
	g++ -g -o $(prog) main.o funciones.o

main.o: main.cpp includes.h globales.h funciones.h
	g++ -c main.cpp

funciones.o: funciones.cpp funciones.h
	g++ -c funciones.cpp

clean:
	rm -f $(prog) *.o