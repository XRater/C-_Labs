all: bin main.exe	
main.exe: bin/main.o bin/phonebook.o
	gcc bin/main.o bin/phonebook.o -o main.exe -lexpat
bin/main.o: src/main.c include/phonebook.h
	gcc -c src/main.c -o bin/main.o
bin/phonebook.o: src/phonebook.c
	gcc -c src/phonebook.c -o bin/phonebook.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main.exe        
