#ifndef ASTAR_H
#define ASTAR_H

#include "Map.h"
#include "Node.hpp"
#include "PathFindingAlgorithm.h"

#include <vector>

class Astar : public PathFindingAlgorithm
{
public:
  Astar(Map* mapStart)
    : PathFindingAlgorithm(mapStart)
  {}
  std::vector<Node> pathFinder(Map* mapStart);
  inline std::vector<Node> shortestPathFinder() { return _shortest; }

private:
  std::vector<Node> _shortest;
  double heuristic(Node a, Node b);
};

#endif
