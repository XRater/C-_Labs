CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++03 -I include -I test
TCXXFLAGS = -O2 -std=c++11 -I include -I test

all: main
main: bin huffman 
test: bin test.exe

huffman: bin/main.o bin/initializer.o bin/huffman.o bin/archiver.o
	$(CXX) bin/main.o bin/initializer.o bin/huffman.o bin/archiver.o -o huffman
bin/main.o: src/main.cpp include/huffman.h include/initializer.h
	$(CXX) -c src/main.cpp $(CXXFLAGS) -o bin/main.o
bin/initializer.o: src/initializer.cpp include/huffman.h include/initializer.h include/exception.h
	$(CXX) -c src/initializer.cpp $(CXXFLAGS) -o bin/initializer.o
bin/huffman.o: src/huffman.cpp include/huffman.h include/archiver.h
	$(CXX) -c src/huffman.cpp $(CXXFLAGS) -o bin/huffman.o
bin/archiver.o: src/archiver.cpp include/archiver.h include/exception.h
	$(CXX) -c src/archiver.cpp $(CXXFLAGS) -o bin/archiver.o

	
test.exe: bin/test.o bin/Test.o bin/InitTest.o bin/HuffmanTest.o bin/ReadPrintTest.o bin/huffman.o bin/initializer.o bin/archiver.o
	$(CXX) bin/test.o bin/Test.o bin/InitTest.o bin/HuffmanTest.o bin/ReadPrintTest.o bin/huffman.o bin/initializer.o bin/archiver.o -o test.exe
bin/test.o: test/test.cpp test/HuffmanTest.h test/InitTest.h test/ReadPrintTest.h include/huffman.h include/initializer.h include/archiver.h
	$(CXX) -c test/test.cpp $(TCXXFLAGS) -o bin/test.o
bin/Test.o: test/Test.cpp test/Test.h
	$(CXX) -c test/Test.cpp $(TCXXFLAGS) -o bin/Test.o
bin/HuffmanTest.o: test/HuffmanTest.cpp test/HuffmanTest.h include/huffman.h
	$(CXX) -c test/HuffmanTest.cpp $(TCXXFLAGS) -o bin/HuffmanTest.o
bin/InitTest.o: test/InitTest.cpp test/InitTest.h include/initializer.h
	$(CXX) -c test/InitTest.cpp $(TCXXFLAGS) -o bin/InitTest.o
bin/ReadPrintTest.o: test/ReadPrintTest.cpp test/ReadPrintTest.h include/archiver.h
	$(CXX) -c test/ReadPrintTest.cpp $(TCXXFLAGS) -o bin/ReadPrintTest.o	    
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm huffman
	rm test.exe   
    
