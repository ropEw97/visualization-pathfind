#ifndef RANDOMMAZE_H
#define RANDOMMAZE_H

#include "Maze.h"

class RandomMaze : public Maze
{
public:
  RandomMaze(int n, int m);
  void generate() override;
};

#endif // RANDOMMAZE_H
