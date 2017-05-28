main: ./bin/main.o ./bin/matrix.o 
	g++ ./bin/main.o ./bin/matrix.o -o main

./bin/main.o: bin ./src/main.cpp ./include/matrix.h
	g++ -c -o ./bin/main.o ./src/main.cpp -Iinclude

./bin/matrix.o: bin ./src/matrix.cpp ./include/matrix.h
	g++ -c -o ./bin/matrix.o ./src/matrix.cpp -Iinclude

clean: 
	rm -rf ./bin
	rm -rf main

bin:
	mkdir bin -p