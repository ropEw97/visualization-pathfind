#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "PathFindingAlgorithm.h"

class DepthFirstSearch : public PathFindingAlgorithm
{
public:
  DepthFirstSearch(Map* mapStart)
    : PathFindingAlgorithm(mapStart){};
  std::vector<Node> pathFinder(Map* mapStart);

  inline std::vector<Node> shortestPathFinder() { return _shortest; }

private:
  std::vector<Node> _shortest;
};

#endif // DEPTHFIRSTSEARCH_H
