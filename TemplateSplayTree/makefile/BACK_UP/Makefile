# Makefile for splay tree, implemented on templates

main: main.o
	g++ main.o -o main
main.o: main.cpp splay_tree.h splay_test.h
	g++ -c main.cpp

clean:
	rm -rf *.o
