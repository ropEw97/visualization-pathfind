PROGRAM   = test.out
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra

$(PROGRAM): test.o Map.o Node.o Map.h Node.hpp
	$(CXX) -o $(PROGRAM) test.o Map.o Node.o


Map.o: Node.cpp Node.hpp Map.cpp Map.h
	$(CXX) -c Map.cpp Node.cpp

Node.o: Node.cpp Node.hpp
	$(CXX) -c Node.cpp


.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
