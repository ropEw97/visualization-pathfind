#include "BreadthFirstSearch.h"

#include <QMap>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <vector>

std::vector<Node>
BreadthFirstSearch::pathFinder(Map* mapStart)
{
  Node startNode = mapStart->getStartNode();

  std::vector<Node> path;
  std::queue<Node> frontier;
  frontier.push(startNode);

  std::set<Node> reached;
  reached.insert(startNode);

  QMap<Node, Node> pred;
  pred[startNode] = startNode;

  while (!frontier.empty()) {
    Node currentNode = frontier.front();
    frontier.pop();

    path.push_back(currentNode);
    if (currentNode.Type() == NodeType::END_NODE) {
      Node c = currentNode;
      _shortest.push_back(c);
      while (c.getX() != pred[c].getX() && c.getY() != pred[c].getY()) {
        _shortest.push_back(pred[c]);
        c = pred[c];
      }

      _shortest.push_back(pred[c]);
      std::reverse(_shortest.begin(), _shortest.end());
      break;
    }
    for (auto nextNode : mapStart->getAdjacentNodes(currentNode)) {
      if (reached.find(nextNode) == reached.end()) {
        frontier.push(nextNode);
        reached.insert(nextNode);
        pred[nextNode] = currentNode;
      }
    }
  }

  if (_shortest.size() == 0)
    pathIsFound = false;

  return path;
}
