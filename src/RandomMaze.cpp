#include "RandomMaze.h"
#include <QRandomGenerator>

RandomMaze::RandomMaze(int n, int m)
  : Maze(n, m)
{
  for (int i = 0; i < _n; i++) {
    for (int j = 0; j < _m; j++) {
      _maze[i][j] = 1;
    }
  }
}

void
RandomMaze::generate()
{
  for (int i = 0; i < _n; i++) {
    for (int j = 0; j < _m; j++) {
      double rng = QRandomGenerator::global()->generateDouble();
      if (rng < 0.33) {
        _maze[i][j] = 0;
      }
    }
  }
}
