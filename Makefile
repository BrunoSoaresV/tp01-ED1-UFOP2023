all: main.o grafo.o
	@gcc main.o grafo.o -o exe
	@rm -r main.o grafo.o
main.o: main.c
	@gcc main.c -c -Wall
grafo.o: grafo.c
	@gcc grafo.c -c -Wall
run:
	@./exe