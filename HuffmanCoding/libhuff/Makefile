#Makefile for huff lib

TEST: test.o libhuff.so
	g++ test.o -L. -lhuff -lboost_unit_test_framework -o TEST
test.o: test.cpp
	g++ -c test.cpp
libhuff.so: Huff.o
	g++ -shared Huff.o -o libhuff.so
Huff.o: Huff.cpp Huff.h
	g++ -c -fPIC Huff.cpp
clean:
	rm -f *.o
