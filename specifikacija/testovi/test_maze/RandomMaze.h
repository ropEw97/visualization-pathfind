#ifndef RANDOMMAZE_H
#define RANDOMMAZE_H

#include "Maze.h"
#include <vector>

class RandomMaze : public Maze
{
public:
    RandomMaze(int n, int m);
    void generate() override;

};

#endif // RANDOMMAZE_H
