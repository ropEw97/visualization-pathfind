PROGRAM   = test.out
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra

$(PROGRAM): test.o Maze.o Kruskal.o RandomMaze.o Maze.h Kruskal.h RandomMaze.h
	$(CXX) -o $(PROGRAM) test.o Maze.o Kruskal.o RandomMaze.o


Kruskal.o: Kruskal.cpp Kruskal.h Maze.cpp Maze.h
	$(CXX) -c Maze.cpp Kruskal.cpp

RandomMaze.o: RandomMaze.cpp RandomMaze.h Maze.cpp Maze.h
	$(CXX) -c Maze.cpp RandomMaze.cpp

Maze.o: Maze.cpp Maze.h
	$(CXX) -c Maze.cpp


.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
