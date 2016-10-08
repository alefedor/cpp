main: ./bin/main.o ./bin/clist.o ./bin/position.o
	gcc ./bin/main.o ./bin/clist.o ./bin/position.o -o main

./bin/main.o: bin ./src/main.c ./include/clist.h ./include/position.h
	gcc -c -o ./bin/main.o ./src/main.c 

./bin/position.o: bin ./src/position.c ./include/position.h
	gcc -c -o ./bin/position.o ./src/position.c

./bin/clist.o: bin ./src/clist.c ./include/clist.h
	gcc -c -o ./bin/clist.o ./src/clist.c

clean: 
	rm -rf ./bin
	rm -rf main

bin:
	mkdir bin -p