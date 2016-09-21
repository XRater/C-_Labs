all: bin test.exe	
test.exe: bin/test.o bin/str.o
	gcc bin/test.o bin/src.o -o test.exe
bin/test.o: test.c str.h
	gcc -c test.c -o bin/test.o
bin/str.o: str.c
	gcc -c str.c -o bin/str.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
        
