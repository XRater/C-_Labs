.PHONY: test

FLAGS := --std=c++14 -I include
LFLAGS := $(FLAGS) -lgtest -lpthread 

all: test

test: bin bin/unit
	bin/unit

bin/unit: bin/unit.o
	g++ $^ $(LFLAGS) -o $@

bin/unit.o: test/unit.cpp include/linq.h
	g++ -c $< $(FLAGS) -o $@

bin:
	mkdir bin
	
clean:
	rm -rf bin
	
