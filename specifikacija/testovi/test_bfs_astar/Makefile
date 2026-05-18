PROGRAM   = test.out
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra

$(PROGRAM): test.o BreadthFirstSearch.o Astar.o BreadthFirstSearch.h Astar.h mapCreating.h Map.o Node.o PathFindingAlgorithm.o
	$(CXX) -o $(PROGRAM) test.o BreadthFirstSearch.o Astar.o Map.o Node.o PathFindingAlgorithm.o


BreadthFirstSearch.o: BreadthFirstSearch.cpp BreadthFirstSearch.h Map.cpp Map.h Node.cpp Node.hpp
	$(CXX) -c BreadthFirstSearch.cpp PathFindingAlgorithm.cpp

Astar.o: Astar.cpp Astar.h Map.cpp Map.h Node.cpp Node.hpp
	$(CXX) -c Astar.cpp PathFindingAlgorithm.cpp

PathFindingAlgorithm.o: PathFindingAlgorithm.cpp PathFindingAlgorithm.h
	$(CXX) -c PathFindingAlgorithm.cpp Map.cpp Node.cpp

Map.o: Map.cpp Map.h Node.cpp Node.hpp
	$(CXX) -c Map.cpp Node.cpp

Node.o: Node.cpp Node.hpp
	$(CXX) -c Node.cpp




.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)



