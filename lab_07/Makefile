all: bin main.exe	
main.exe: bin/main.o bin/my_vector.o
	g++ bin/main.o bin/my_vector.o -o main.exe
bin/main.o: src/main.cpp include/my_vector.h
	g++ -c src/main.cpp -std=c++11 -o bin/main.o
bin/my_vector.o: src/my_vector.cpp include/my_vector.h
	g++ -c src/my_vector.cpp -std=c++11 -o bin/my_vector.o
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main.exe        
