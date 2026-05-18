#ifndef DRAWNODEMOVABLE_H
#define DRAWNODEMOVABLE_H

#include "DrawNode.h"

class DrawNodeMovable : public DrawNode
{
public:
  DrawNodeMovable(Node* node,
                  const QPixmap& pixmap,
                  const int moveWidth,
                  const int moveHeight);

private:
  const int _moveWidth;
  const int _moveHeight;

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // DRAWNODEMOVABLE_H
