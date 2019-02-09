all: Life
	./Life.out
Life.o: Life.cpp
	clang++-7 -std=c++11 -c Life.cpp
Life: Life.o
	clang++-7 -std=c++11 Life.o -o Life.out