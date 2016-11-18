all: bin main	
main: bin/main.o bin/bmp_init.o bin/bmp_rotate.o bin/bmp_cr.o
	gcc bin/main.o bin/bmp_init.o bin/bmp_rotate.o bin/bmp_cr.o -std=c99 -I include -Wall -Werror -o main
bin/main.o: src/main.c include/bmp.h include/bmp_struct.h include/bmp_init.h include/bmp_rotate.h include/bmp_cr.h
	gcc -c src/main.c -std=c99 -I include -Wall -Werror -o bin/main.o
bin/bmp_init.o: src/bmp_init.c include/bmp.h include/bmp_struct.h include/bmp_init.h
	gcc -c src/bmp_init.c -std=c99 -I include -Wall -Werror -o bin/bmp_init.o
bin/bmp_rotate.o: src/bmp_rotate.c include/bmp_struct.h include/bmp_rotate.h 
	gcc -c src/bmp_rotate.c -std=c99 -I include -Wall -Werror -o bin/bmp_rotate.o
bin/bmp_cr.o: src/bmp_cr.c include/bmp_struct.h include/bmp_cr.h
	gcc -c src/bmp_cr.c -std=c99 -I include -Wall -Werror -o bin/bmp_cr.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main      
