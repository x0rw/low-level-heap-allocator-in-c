all:program


program: main.o 
	gcc build/main.o -std=c99 -lm  -g -o bin/main


main.o: main.c 
	gcc -c main.c -o build/main.o -ggdb -g 

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
