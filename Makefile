Matrix.o: Matrix.h Matrix.cpp
	g++ -c Matrix.cpp

main.o: main.cpp
	g++ -c main.cpp

build: Matrix.o main.o
	g++ Matrix.o main.o -o output

run:
	./output

clean:
	rm output *.o