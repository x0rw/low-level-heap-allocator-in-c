all:program run


program: main.o arena.o allocator.o memory_worker.o
	gcc build/main.o build/arena.o build/allocator.o build/memory_worker.o -pthread -std=c99 -lm  -g -o bin/main


main.o: main.c 
	gcc -c main.c -o build/main.o -ggdb -g 

arena.o: src/arena.c 
	gcc -c src/arena.c -o build/arena.o -ggdb -g 

allocator.o: src/allocator.c 
	gcc -c src/allocator.c -o build/allocator.o -ggdb -g 

memory_worker.o: src/memory_worker.c 
	gcc -c src/memory_worker.c -o build/memory_worker.o -ggdb -g 

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
