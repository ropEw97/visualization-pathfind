#include "DrawNodeMovable.h"

#include <QGraphicsSceneMouseEvent>

DrawNodeMovable::DrawNodeMovable(Node* node,
                                 const QPixmap& pixmap,
                                 const int moveWidth,
                                 const int moveHeight)
  : DrawNode(node, pixmap)
  , _moveWidth(moveWidth)
  , _moveHeight(moveHeight)
{
  setFlags(GraphicsItemFlag::ItemIsSelectable |
           GraphicsItemFlag::ItemIsMovable);
}

void
DrawNodeMovable::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsPixmapItem::mouseMoveEvent(event);
  int x = this->x();
  int y = this->y();
  if (x < 0) {
    x = 0;
  } else if (x > _moveWidth - _dim) {
    x = _moveWidth - _dim;
  }
  if (y < 0) {
    y = 0;
  } else if (y > _moveHeight - _dim) {
    y = _moveHeight - _dim;
  }
  this->setPos(x, y);
}
