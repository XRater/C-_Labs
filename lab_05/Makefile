all: bin main.exe	
main.exe: bin/main.o bin/clist.o bin/position.o
	gcc bin/main.o bin/clist.o bin/position.o -o main.exe
bin/main.o: src/main.c include/position.h
	gcc -c src/main.c -o bin/main.o
bin/position.o: src/position.c include/position.h
	gcc -c src/position.c -o bin/position.o
bin/clist.o: src/clist.c include/clist.h
	gcc -c src/clist.c -o bin/clist.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main.exe        
