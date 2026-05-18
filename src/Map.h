#ifndef MAP_H
#define MAP_H

#include "Node.hpp"
#include <vector>

using Point = std::pair<int, int>;

class Map
{
public:
  Map(int startX,
      int startY,
      int endX,
      int endY,
      int width,
      int height,
      int size);

  std::vector<Node> getAdjacentNodes(const Node& node) const;
  Node getStartNode() const;
  Node getEndNode() const;

  Node getNode(unsigned i, unsigned j) const;
  void setNode(unsigned i, unsigned j, const Node& node);
  std::pair<int, int> getIndices(int x, int y) const;
  std::vector<Point> getNodePolygon(int xPos, int yPos) const;
  unsigned width() const;
  unsigned height() const;

private:
  std::vector<std::vector<Node>> m_matrix;
  int m_startX;
  int m_startY;
  int m_endX;
  int m_endY;
  int m_originX;
  int m_originY;
  int m_size;

  void setOrigin();
  void resizeMatrix(int width, int height);
  void fillMatrix();
  std::vector<std::pair<int, int>> getAdjacentIndices(int i, int j) const;
};

#endif // MAP_H
