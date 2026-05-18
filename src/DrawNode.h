#ifndef DRAWNODE_H
#define DRAWNODE_H

#include "Node.hpp"
#include <QGraphicsPixmapItem>

class DrawNode : public QGraphicsPixmapItem
{
public:
  DrawNode(Node* node, const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

  QRectF boundingRect() const;
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget);
  int dim() const;
  static int dim(NodeType);

  Node* node();

protected:
  Node* _node;
  int _dim;
};

#endif // DRAWNODE_H
