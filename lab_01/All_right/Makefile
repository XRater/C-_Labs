lab1/make.exe: bin/main.o bin/algorithm.o bin/util.o bin/io.o bin lab1
	gcc bin/main.o bin/algorithm.o bin/util.o bin/io.o -o lab1/main.exe
bin/main.o: src//main.c include/algorithm.h include/util.h include/io.h bin
	gcc -c src/main.c -o bin/main.o
bin/algorithm.o: src/algorithm.c include/util.h include/io.h bin
	gcc -c src/algorithm.c -o bin/algorithm.o
bin/util.o: src/util.c include/io.h bin
	gcc -c src/util.c -o bin/util.o
bin/io.o: src/io.c bin
	gcc -c src/io.c -o bin/io.o
bin:
	mkdir -p bin
lab1:
	mkdir -p lab1
clean:
	rm -r -f bin
	rm -r -f lab1	
        
