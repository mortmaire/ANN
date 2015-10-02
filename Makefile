CC=g++
CFLAGS=-O2
LFLAGS=

main: main.cpp
# 	g++ main.cpp -o m $(LFLAGS) $(CFLAGS)-O2
	g++ main.cpp -o m -O2 -lpng