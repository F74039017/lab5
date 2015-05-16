all: main.o HugeInt.o
	g++ -o lab5 main.o HugeInt.o

main.o: main.cpp HugeInt.h
	g++ -c main.cpp

HugeInt.o: HugeInt.cpp HugeInt.h
	g++ -c HugeInt.cpp

clean:
	rm lab5 *.o
