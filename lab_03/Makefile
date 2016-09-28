all: bin main.exe	
main.exe: bin/main.o bin/clist.o
	gcc bin/main.o bin/clist.o -o main.exe
bin/main.o: src/main.c include/clist.h
	gcc -c src/main.c -o bin/main.o
bin/clist.o: src/clist.c
	gcc -c src/clist.c -o bin/clist.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main.exe        
