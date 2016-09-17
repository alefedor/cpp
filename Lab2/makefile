test: ./bin/test_str.o ./bin/str.o ./bin/test.o 
	gcc ./bin/test_str.o ./bin/str.o ./bin/test.o -o test

./bin/test_str.o: bin ./src/test_str.c ./include/test_str.h
	gcc -c -o ./bin/test_str.o ./src/test_str.c 

./bin/test.o: bin ./src/test.c
	gcc -c -o ./bin/test.o ./src/test.c

./bin/str.o: bin ./src/str.c ./include/str.h 
	gcc -c -o ./bin/str.o ./src/str.c

clean: 
	rm -rf ./bin
	rm -rf test

bin:
	mkdir bin -p