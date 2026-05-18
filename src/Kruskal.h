#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Maze.h"

class Kruskal : public Maze
{
public:
  Kruskal(int n, int m);
  void generate() override;

private:
  MapaParova celije;
  VektorParova zidovi;
};

#endif // KRUSKAL_H
