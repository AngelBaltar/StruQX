
all:
	bison -o interprete_query.tab.c interprete_query.y -yd
	flex -o interprete_query.c interprete_query.l
	gcc -I . -O2 lib_utils.c interprete_query.c interprete_query.tab.c -o interprete -lfl -ly -ll -fopenmp
	rm interprete_query.tab.c interprete_query.tab.h interprete_query.c
clean:
	rm interprete

run:
	./interprete