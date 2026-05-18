#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "Map.h"
#include "Node.hpp"
#include "PathFindingAlgorithm.h"

#include <vector> 

class BreadthFirstSearch : public PathFindingAlgorithm {
	public:
		BreadthFirstSearch(Map* mapStart): PathFindingAlgorithm(mapStart) {}
		std::vector<Node> pathFinder(Map* mapStart);
        inline std::vector<Node> shortestPathFinder(){ return _shortest;}


    private:
        std::vector<Node> _shortest;
};

#endif

