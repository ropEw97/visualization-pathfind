#include "Map.h"

Map::Map(int startX,
         int startY,
         int endX,
         int endY,
         int width,
         int height,
         int size)
  : m_startX(startX)
  , m_startY(startY)
  , m_endX(endX)
  , m_endY(endY)
  , m_size(size)
{
  if (m_size % 4 != 0)
    m_size = (m_size / 4) * 4;

  setOrigin();
  resizeMatrix(width, height);
  fillMatrix();
}

void
Map::setOrigin()
{
  m_originX = m_startX % static_cast<int>(m_size * 1.5);
  m_originY = m_startY;
  if (m_originX >= m_size * 0.75) {
    m_originX -= m_size * 0.75;
    m_originY += m_size * 0.5;
  }

  m_originY = m_originY % m_size;
}

void
Map::resizeMatrix(int width, int height)
{
  int numRows, numColumns;

  numRows = (height - m_originY) / m_size;
  if ((height - m_originY) % m_size < m_size * 0.5 && m_originY < m_size * 0.5)
    numRows--;

  numColumns = ((width - m_originX) / static_cast<int>(m_size * 1.5)) * 2;
  if ((width - m_originX) % static_cast<int>(m_size * 1.5) > m_size)
    numColumns++;

  m_matrix.resize(numRows);
  for (auto& row : m_matrix)
    row.resize(numColumns);
}

void
Map::fillMatrix()
{
  int numRows = m_matrix.size();
  int numColumns = m_matrix[0].size();

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      int xPos = m_originX, yPos = m_originY;

      xPos += (j / 2) * (m_size * 1.5);
      yPos += i * m_size;

      if (j % 2 == 1) {
        xPos += m_size * 0.75;
        if (m_originY < m_size * 0.5)
          yPos += m_size * 0.5;
        else
          yPos -= m_size * 0.5;
      }

      setNode(i, j, Node(NodeType::WEIGHTED_NODE, xPos, yPos));
    }
  }
}

void
Map::setNode(unsigned i, unsigned j, const Node& node)
{
  if (i >= m_matrix.size() || j >= m_matrix[0].size())
    return;
  m_matrix[i][j] = node;
}

Node
Map::getNode(unsigned i, unsigned j) const
{
  if (i >= m_matrix.size() || j >= m_matrix[0].size())
    return Node();
  return m_matrix[i][j];
}

std::pair<int, int>
Map::getIndices(int x, int y) const
{
  int i, j;
  x -= m_originX;
  y -= m_originY;

  if (x < 0)
    x = 0;
  if (y < 0)
    y = 0;

  j = (x / static_cast<int>(m_size * 1.5)) * 2;
  if (x % static_cast<int>(m_size * 1.5) != 0) {
    j++;
    if (m_originY < m_size * 0.5)
      y -= m_size * 0.5;
    else
      y += m_size * 0.5;
  }
  i = y / m_size;

  return std::make_pair(i, j);
}

unsigned
Map::height() const
{
  return m_matrix.size();
}

unsigned
Map::width() const
{
  if (m_matrix.empty())
    return 0;
  return m_matrix[0].size();
}

std::vector<Point>
Map::getNodePolygon(int xPos, int yPos) const
{
  std::vector<Point> points = { { 0, 0.5 * m_size },
                                { 0.25 * m_size, 0 },
                                { 0.75 * m_size, 0 },
                                { 1.0 * m_size, 0.5 * m_size },
                                { 0.75 * m_size, 1.0 * m_size },
                                { 0.25 * m_size, 1.0 * m_size },
                                { 0, 0.5 * m_size } };
  for (auto& point : points) {
    point.first += xPos;
    point.second += yPos;
  }
  return points;
}

std::vector<std::pair<int, int>>
Map::getAdjacentIndices(int i, int j) const
{
  std::vector<std::pair<int, int>> directions;

  if ((m_originY < m_size * 0.5 && j % 2 == 0) ||
      (m_originY >= m_size * 0.5 && j % 2 != 0)) {
    directions = { { -1, -1 }, { -1, 0 }, { -1, 1 },
                   { 0, -1 },  { 1, 0 },  { 0, 1 } };
  } else {
    directions = {
      { 0, -1 }, { -1, 0 }, { 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }
    };
  }

  std::vector<std::pair<int, int>> neighborIndices;
  for (auto& dir : directions) {
    neighborIndices.emplace_back(i + dir.first, j + dir.second);
  }

  return neighborIndices;
}

std::vector<Node>
Map::getAdjacentNodes(const Node& node) const
{
  std::pair<int, int> indices = getIndices(node.getX(), node.getY());

  std::vector<std::pair<int, int>> neighborIndices;
  neighborIndices = getAdjacentIndices(indices.first, indices.second);

  std::vector<double> dirWeights = { 0.9, 1, 0.9, 0.9, 1, 0.9 };

  std::vector<Node> neighbors;

  for (unsigned i = 0; i < neighborIndices.size(); i++) {
    int row = neighborIndices[i].first;
    int col = neighborIndices[i].second;

    if (row < 0 || static_cast<unsigned>(row) >= height() || col < 0 ||
        static_cast<unsigned>(col) >= width())
      continue;

    Node current = m_matrix[row][col];

    if (current.getWeight() < 0)
      continue;

    neighbors.push_back(Node(current.Type(),
                             current.getWeight() * dirWeights[i] * m_size,
                             current.getX(),
                             current.getY()));
  }

  return neighbors;
}

Node
Map::getStartNode() const
{
  std::pair<int, int> startIndices = getIndices(m_startX, m_startY);
  return m_matrix[startIndices.first][startIndices.second];
}

Node
Map::getEndNode() const
{
  return Node(NodeType::END_NODE, m_endX, m_endY);
}
