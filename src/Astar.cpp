#include "Astar.h"

#include <QMap>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <vector>

double
Astar::heuristic(Node a, Node b)
{
  int x_a = a.getX();
  int x_b = b.getX();
  int y_a = a.getY();
  int y_b = b.getY();

  double h = std::abs(x_a - x_b) + std::abs(y_a - y_b);

  return h;
}

std::vector<Node>
Astar::pathFinder(Map* mapStart)
{

  Node startNode = mapStart->getStartNode();
  Node endNode = mapStart->getEndNode();

  std::set<Node> open_list;
  open_list.insert(startNode);
  std::set<Node> closed_list;

  std::vector<Node> path;
  path.push_back(startNode);

  std::map<Node, double> g;

  g[startNode] = 0;

  QMap<Node, Node> parents;
  parents[startNode] = startNode;

  while (!open_list.empty()) {

    auto current_it = open_list.begin();
    Node n = *current_it;

    for (auto it = open_list.begin(); it != open_list.end(); it++) {
      auto v = *it;
      if (g[v] + heuristic(v, endNode) < g[n] + heuristic(n, endNode)) {
        n = v;
        current_it = it;
      }
    }

    if (n.Type() == NodeType::END_NODE) {
      Node c = n;
      _shortest.push_back(c);
      while (
        !(c.getX() == parents[c].getX() && c.getY() == parents[c].getY())) {
        _shortest.push_back(parents[c]);
        c = parents[c];
      }

      _shortest.push_back(parents[c]);
      std::reverse(_shortest.begin(), _shortest.end());

      pathIsFound = true;
      return path;
    }

    for (Node m : mapStart->getAdjacentNodes(n)) {

      if ((open_list.find(m) == open_list.end()) &&
          (closed_list.find(m) == closed_list.end())) {
        open_list.insert(m);
        parents[m] = n;
        g[m] = g[n] + m.getWeight();
        path.push_back(m);
      }

      else {
        if (g[m] > g[n] + m.getWeight()) {
          g[m] = g[n] + m.getWeight();
          parents[m] = n;

          if (closed_list.find(m) != closed_list.end()) {
            closed_list.erase(m);
            open_list.insert(m);
            path.push_back(m);
          }
        }
      }
    }

    open_list.erase(n);
    closed_list.insert(n);
  }

  if (_shortest.size() == 0)
    pathIsFound = false;

  return path;
}
