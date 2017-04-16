CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++03 -I include -I test

all: main
main: bin huffman 
test: bin test.exe

huffman: bin/main.o bin/huffman.o
	$(CXX) bin/main.o bin/huffman.o -o huffman
bin/main.o: src/main.cpp include/huffman.h include/double_queue.h
	$(CXX) -c src/main.cpp $(CXXFLAGS) -o bin/main.o
bin/huffman.o: src/huffman.cpp include/huffman.h include/double_queue.h
	$(CXX) -c src/huffman.cpp $(CXXFLAGS) -o bin/huffman.o
#test.exe: bin/test.o bin/Test.o bin/Boardtest.o bin/gamemodel.o
#	$(CXX) bin/test.o bin/Test.o bin/Boardtest.o bin/gamemodel.o -o test.exe
#bin/test.o: test/test.cpp test/Boardtest.h include/gamemodel.h
#	$(CXX) -c test/test.cpp $(CXXFLAGS) -o bin/test.o
#bin/Test.o: test/Test.cpp test/Test.h
#	$(CXX) -c test/Test.cpp $(CXXFLAGS) -o bin/Test.o
#bin/Boardtest.o: test/Boardtest.cpp test/Boardtest.h
#	$(CXX) -c test/Boardtest.cpp $(CXXFLAGS) -o bin/Boardtest.o
    
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm huffman
	rm test.exe   
    
