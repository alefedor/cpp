main: ./bin/main.o ./bin/Board.o ./bin/BoardView.o
	g++ ./bin/main.o ./bin/Board.o ./bin/BoardView.o -o main

./bin/main.o: bin ./src/main.cpp
	g++ -c -o ./bin/main.o ./src/main.cpp -Wall -Werror -std=c++11

./bin/Board.o: bin ./src/Board.cpp ./include/Board.h
	g++ -c -o ./bin/Board.o ./src/Board.cpp -Wall -Werror -std=c++11

./bin/BoardView.o: bin ./src/BoardView.cpp ./include/BoardView.h
	g++ -c -o ./bin/BoardView.o ./src/BoardView.cpp -Wall -Werror -std=c++11

clean: 
	rm -rf ./bin
	rm -rf main

bin:
	mkdir bin -p