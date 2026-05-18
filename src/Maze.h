#ifndef MAZE_H
#define MAZE_H

#include <QSharedPointer>

using VektorParova = std::vector<std::pair<int, int>>;
using ParParova = std::pair<std::pair<int, int>, std::pair<int, int>>;
using MapaParova = std::map<std::pair<int, int>, std::pair<int, int>>;
using Par = std::pair<int, int>;

class Maze
{
public:
  Maze() = delete;
  VektorParova getObstacles();
  void print();
  virtual void generate() = 0;
  virtual ~Maze();

protected:
  Maze(int n, int m);
  int _n;
  int _m;
  int** _maze;
  void generateKruskal();
};

#endif // MAZE_H
