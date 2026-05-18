#include "Node.hpp"

static const double DEFAULT_WEIGHT = 1.0;

Node::Node(NodeType type, int x, int y)
  : m_x(x)
  , m_y(y)
  , m_type(type)
{
  m_weight = DEFAULT_WEIGHT;
}

Node::Node(NodeType type, double weight, int x, int y)
  : Node(type, x, y)
{
  if (type == NodeType::WEIGHTED_NODE)
    m_weight = weight;
}

Node::Node()
  : Node(NodeType::WEIGHTED_NODE, 0, 0)
{}

int
Node::getX() const
{
  return m_x;
}
int
Node::getY() const
{
  return m_y;
}
double
Node::getWeight() const
{
  return m_weight;
}
NodeType
Node::Type() const
{
  return m_type;
}

void
Node::setX(int x)
{
  m_x = x;
}

void
Node::setY(int y)
{
  m_y = y;
}

bool
Node::operator==(const Node& other) const
{
  return (this->m_x == other.m_x && this->m_y == other.m_y);
}

bool
Node::operator<(const Node& other) const
{
  if (this->m_x == other.m_x)
    return this->m_y < other.m_y;
  else
    return this->m_x < other.m_x;
}

bool
Node::operator!=(const Node& other) const
{
  return !(*this == other);
}
