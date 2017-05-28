main: ./bin/main.o ./bin/bmp.o
	gcc ./bin/main.o ./bin/bmp.o -o main

./bin/main.o: bin ./src/main.c
	gcc -c -o ./bin/main.o ./src/main.c -std=c99 -Wall -Werror

./bin/bmp.o: bin ./src/bmp.c ./include/bmp.h
	gcc -c -o ./bin/bmp.o ./src/bmp.c -std=c99 -Wall -Werror

clean: 
	rm -rf ./bin
	rm -rf main

bin:
	mkdir bin -p