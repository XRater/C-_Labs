all: bin main.exe	
main.exe: bin/main.o bin/str.o  bin/tests.o bin
	gcc bin/main.o bin/tests.o bin/str.o -o main.exe
bin/main.o: src/main.c include/str.h bin
	gcc -c src/main.c -o bin/main.o
bin/tests.o: src/tests.c include/str.h bin
	gcc -c src/tests.c -o bin/tests.o
bin/str.o: src/str.c
	gcc -c src/str.c -o bin/str.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main.exe
        
