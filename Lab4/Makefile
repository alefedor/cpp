ms_cli: ./bin/mergesort.o
	gcc ./bin/mergesort.o -o ms_cli

./bin/mergesort.o: bin ./src/mergesort.c 
	gcc -c -o ./bin/mergesort.o ./src/mergesort.c 

clean: 
	rm -rf ./bin
	rm -rf ms_cli

bin:
	mkdir bin -p