empl_db: ./bin/main.o ./bin/employees.o
	g++ ./bin/main.o ./bin/employees.o -o empl_db

./bin/main.o: bin ./src/main.cpp ./include/employees.h
	g++ -c -o ./bin/main.o ./src/main.cpp

./bin/employees.o: bin ./src/employees.cpp ./include/employees.h
	g++ -c -o ./bin/employees.o ./src/employees.cpp

clean: 
	rm -rf ./bin
	rm -rf empl_db

bin:
	mkdir bin -p