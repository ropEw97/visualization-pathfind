PROGRAM   = test.out
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra

$(PROGRAM): test.o DepthFirstSearch.o Dijkstra.o DepthFirstSearch.h Dijkstra.h mapCreating.h Map.o Node.o PathFindingAlgorithm.o
	$(CXX) -o $(PROGRAM) test.o DepthFirstSearch.o Dijkstra.o Map.o Node.o PathFindingAlgorithm.o

DepthFirstSearch.o: DepthFirstSearch.cpp DepthFirstSearch.h Map.cpp Map.h Node.cpp Node.hpp
	$(CXX) -c DepthFirstSearch.cpp PathFindingAlgorithm.cpp

Dijkstra.o: Dijkstra.cpp Dijkstra.h Map.cpp Map.h Node.cpp Node.hpp
	$(CXX) -c Dijkstra.cpp PathFindingAlgorithm.cpp

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



