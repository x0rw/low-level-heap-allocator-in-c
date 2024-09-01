all:program run


program: main.o arena.o
	gcc build/main.o build/arena.o -std=c99 -lm  -g -o bin/main


main.o: main.c 
	gcc -c main.c -o build/main.o -ggdb -g 

arena.o: src/arena.c 
	gcc -c src/arena.c -o build/arena.o -ggdb -g 

clean:
	rm build/*.o 
	rm bin/*
run:
	./bin/main
debug:
	gdb ./bin/main

valgrind:
	valgrind ./bin/main
gdb:
	gdb ./bin/main
