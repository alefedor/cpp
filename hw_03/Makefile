main: ./bin/main.o ./bin/huffman.o 
	g++ ./bin/main.o ./bin/huffman.o -o huffman

./bin/main.o: bin ./src/main.cpp ./include/huffman.h
	g++ -c -o ./bin/main.o ./src/main.cpp -Iinclude -Wall -Wextra -O2

./bin/huffman.o: bin ./src/huffman.cpp ./include/huffman.h
	g++ -c -o ./bin/huffman.o ./src/huffman.cpp -Iinclude -Wall -Wextra -O2

clean: 
	rm -rf ./bin
	rm -rf huffman

bin:
	mkdir bin -p