#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include "Map.h"
#include "Node.hpp"
#include <vector>

class PathFindingAlgorithm
{
public:
  bool pathIsFound = false;
  PathFindingAlgorithm(Map* mapStart);
  virtual std::vector<Node> pathFinder(Map* mapStart) = 0;
  inline std::vector<Node> shortestPathFinder() { return _shortest; };

protected:
  Map* m_map;
  std::vector<Node> _shortest;
};

#endif // PATHFINDINGALGORITHM_H
