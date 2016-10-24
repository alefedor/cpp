main: ./bin/main.o
	gcc ./bin/main.o -o main -lexpat

./bin/main.o: bin ./src/main.c ./include/names.h
	gcc -c -o ./bin/main.o ./src/main.c -lexpat

clean: 
	rm -rf ./bin
	rm -rf main

bin:
	mkdir bin -p