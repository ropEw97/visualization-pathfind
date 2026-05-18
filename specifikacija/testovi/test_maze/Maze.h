#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <map>
#include <iostream>

using VektorParova = std::vector<std::pair<int,int>>;
using ParParova = std::pair<std::pair<int,int>,std::pair<int,int>>;
using MapaParova = std::map<std::pair<int,int>,std::pair<int,int>>;
using Par = std::pair<int,int>;

class Maze
{
public:
    Maze() = delete;
    VektorParova getObstacles();
    void print();
    virtual void generate() = 0;
    virtual ~Maze();
    int getN() const;
    int getM() const;

protected:
    Maze(int n, int m);
    int _n;
    int _m;
    int** _maze;
 };

#endif // MAZE_H
