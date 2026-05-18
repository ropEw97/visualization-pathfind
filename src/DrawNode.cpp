#include "DrawNode.h"

#include <QPainter>

DrawNode::DrawNode(Node* node, const QPixmap& pixmap, QGraphicsItem* parent)
  : QGraphicsPixmapItem(pixmap, parent)
  , _node(node)
{
  _dim = dim(_node->Type());
  setPixmap(pixmap.scaled(_dim, _dim));
  setPos(_node->getX(), _node->getY());
  setZValue(1);
}

int
DrawNode::dim() const
{
  return _dim;
}

int
DrawNode::dim(NodeType type)
{
  if (NodeType::WEIGHTED_NODE == type)
    return 20;
  else
    return 30;
}

Node*
DrawNode::node()
{
  return _node;
}

QRectF
DrawNode::boundingRect() const
{
  return QRectF(0, 0, _dim, _dim);
}

void
DrawNode::paint(QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->drawPixmap(boundingRect(), pixmap(), boundingRect());
}
