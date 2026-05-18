#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "PathFindingAlgorithm.h"

class Dijkstra : public PathFindingAlgorithm
{
public:
  Dijkstra(Map* mapStart)
    : PathFindingAlgorithm(mapStart){};
  std::vector<Node> pathFinder(Map* mapStart);
  inline std::vector<Node> shortestPathFinder() { return _shortest; }

private:
  std::vector<Node> _shortest;
};
#endif // DIJKSTRA_H
