hash:hash.o hash.h
	gcc -g -ansi -Wall -pedantic hash.o -o hash
hash.o: hash.c hash.h
	gcc -c -ansi -Wall -pedantic hash.c -o hash.o
