#include "Maze.h"
#include <QDebug>
#include <algorithm>
#include <random>

Maze::Maze(int n, int m)
  : _n(n)
  , _m(m)
{
  _maze = new int*[_n];
  for (int i = 0; i < _n; i++) {
    _maze[i] = new int[_m];
  }
}

VektorParova
Maze::getObstacles()
{
  VektorParova obstacles;
  for (int i = 0; i < _n; i++) {
    for (int j = 0; j < _m; j++) {
      if (_maze[i][j] == 0) {
        obstacles.push_back(std::pair(i, j));
      }
    }
  }
  return obstacles;
}

void
Maze::print()
{
  for (int i = 0; i < _n; i++) {
    std::string str;
    for (int j = 0; j < _m; j++) {
      str.append(std::to_string(_maze[i][j]));
    }
    qInfo() << QString::fromStdString(str);
  }
}

Maze::~Maze()
{
  for (int i = 0; i < _n; ++i)
    delete[] _maze[i];
  delete[] _maze;
}
