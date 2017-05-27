.PHONY: test

FLAGS := --std=c++14 -I include -I test
LFLAGS := $(FLAGS) -lgtest -lpthread 
TESTSH := test/unit_base.h test/unit_class.h

all: test

test: bin bin/unit
	bin/unit

bin/unit: bin/unit.o
	g++ $^ $(LFLAGS) -o $@

bin/unit.o: test/unit.cpp include/linq.h $(TESTSH)
	g++ -c $< $(FLAGS) -o $@

bin:
	mkdir bin
	
clean:
	rm -rf bin
	
