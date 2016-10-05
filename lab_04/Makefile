all: bin main.exe	
main.exe: bin/ms_cli.o bin/mergesort.o
	gcc bin/ms_cli.o bin/mergesort.o -o main.exe
bin/ms_cli.o: src/ms_cli.c include/mergesort.h
	gcc -c src/ms_cli.c -o bin/ms_cli.o
bin/mergesort.o: src/mergesort.c
	gcc -c src/mergesort.c -o bin/mergesort.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main.exe        
