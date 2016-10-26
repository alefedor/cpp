main: ./bin/main.o ./bin/phonebook.o
	gcc ./bin/main.o ./bin/phonebook.o -o main -lexpat

./bin/main.o: bin ./src/main.c ./include/names.h
	gcc -c -o ./bin/main.o ./src/main.c

./bin/phonebook.o: bin ./src/phonebook.c ./include/phonebook.h
	gcc -c -o ./bin/phonebook.o ./src/phonebook.c

clean: 
	rm -rf ./bin
	rm -rf main

bin:
	mkdir bin -p