pose_db: ./bin/main.o ./bin/clist.o 
	gcc ./bin/main.o ./bin/clist.o -o pose_db

./bin/main.o: bin ./src/main.c ./include/clist.h
	gcc -c -o ./bin/main.o ./src/main.c 

./bin/clist.o: bin ./src/clist.c ./include/clist.h
	gcc -c -o ./bin/clist.o ./src/clist.c

clean: 
	rm -rf ./bin
	rm -rf pose_db

bin:
	mkdir bin -p