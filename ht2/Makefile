CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++11 -I include -I test

all: bin main test

main: bin/main.o bin/gameview.o bin/gamemodel.o
	$(CXX) bin/main.o bin/gameview.o bin/gamemodel.o -o main.exe
bin/main.o: src/main.cpp include/gameview.h
	$(CXX) -c src/main.cpp $(CXXFLAGS) -o bin/main.o
bin/gameview.o: src/gameview.cpp include/gameview.h include/gamemodel.h
	$(CXX) -c src/gameview.cpp $(CXXFLAGS) -o bin/gameview.o
bin/gamemodel.o: src/gamemodel.cpp include/gamemodel.h
	$(CXX) -c src/gamemodel.cpp $(CXXFLAGS) -o bin/gamemodel.o
test: bin/test.o bin/Test.o bin/Boardtest.o bin/gamemodel.o
	$(CXX) bin/test.o bin/Test.o bin/Boardtest.o bin/gamemodel.o -o test.exe
bin/test.o: test/test.cpp test/Boardtest.h include/gamemodel.h
	$(CXX) -c test/test.cpp $(CXXFLAGS) -o bin/test.o
bin/Test.o: test/Test.cpp test/Test.h
	$(CXX) -c test/Test.cpp $(CXXFLAGS) -o bin/Test.o
bin/Boardtest.o: test/Boardtest.cpp test/Boardtest.h
	$(CXX) -c test/Boardtest.cpp $(CXXFLAGS) -o bin/Boardtest.o
    
bin:
	mkdir -p bin
clean:
	rm -r -f bin
	rm main.exe
	rm test.exe   
    
