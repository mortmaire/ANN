CC=g++
CFLAGS=-O2
LFLAGS=

main: main.cpp
	g++ main.cpp -o m $(LFLAGS) $(CFLAGS)