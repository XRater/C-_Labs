all: bin main	
main: bin/main.o bin/bmp.o
	gcc bin/main.o bin/bmp.o -std=c99 -I include -Wall -Werror -o main
bin/main.o: src/main.c include/bmp.h
	gcc -c src/main.c -std=c99 -I include -Wall -Werror -o bin/main.o
bin/bmp.o: src/bmp.c include/bmp.h
	gcc -c src/bmp.c -std=c99 -I include -Wall -Werror -o bin/bmp.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main      
