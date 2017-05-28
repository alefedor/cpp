main: ./bin/main.o
	g++ ./bin/main.o -o main

./bin/main.o: bin ./src/main.cpp ./include/my_array.h
	g++ -c -o ./bin/main.o ./src/main.cpp -Iinclude

clean: 
	rm -rf ./bin
	rm -rf main

bin:
	mkdir bin -p