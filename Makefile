all: parse

parse: tokenise.o ast.o parse.o
	gcc -Wall tokenise.o ast.o parse.o -o parse

tokeniser.o: tokenise.c
	gcc -Wall -c tokenise.c

ast.o: ast.c
	gcc -Wall -c ast.c

parse.o: parse.c
	gcc -Wall -c parse.c

clean:
	rm -rf *.o parser
