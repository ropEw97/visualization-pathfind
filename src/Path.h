#ifndef PATH_H
#define PATH_H

#include "Canvas.h"
#include <vector>

enum class PathType
{
  WORKING_PATH,
  FINAL_PATH
};

class Path : public QGraphicsObject
{
  Q_OBJECT

public:
  static const int path_speed = 20;

  Path(const std::vector<Node>& path,
       PathType type,
       int speed = path_speed,
       int index = 0,
       QGraphicsItem* parent = nullptr);
  void drawNext();
  QRectF boundingRect() const;
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget);

signals:
  void pathFinishedDrawing(PathType type);

private:
  QColor getColor() const;

  std::vector<std::pair<int, int>> m_path;
  unsigned m_index;
  PathType m_type;
  int m_speed;
  int m_nodeSize;
};

#endif // PATH_H
