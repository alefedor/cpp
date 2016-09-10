lab1: ./bin/util.o ./bin/io.o ./bin/algorithm.o ./bin/main.o
	gcc ./bin/algorithm.o ./bin/util.o ./bin/io.o ./bin/main.o -o lab1

./bin/main.o: ./src/main.c
	mkdir -p bin
	gcc -c -o ./bin/main.o ./src/main.c 

./bin/io.o: ./src/io.c
	mkdir -p bin
	gcc -c -o ./bin/io.o ./src/io.c

./bin/algorithm.o: ./src/algorithm.c
	mkdir -p bin
	gcc -c -o ./bin/algorithm.o ./src/algorithm.c

./bin/util.o: ./src/util.c
	mkdir -p bin
	gcc -c -o ./bin/util.o ./src/util.c

clean: 
	rm -rf ./bin

	