#ifndef CANVAS_H
#define CANVAS_H

#include "DrawNode.h"
#include "DrawNodeMovable.h"
#include "Map.h"
#include "Maze.h"
#include <QGraphicsScene>

class Canvas : public QGraphicsScene
{
public:
  explicit Canvas(QObject* parent = nullptr);

  void AddNode(const int x, const int y, const ObstacleWeight type);
  DrawNodeMovable* getStart();
  DrawNodeMovable* getTarget();
  std::vector<DrawNode*>* getObstacles();
  Map* generateMap();

  static const int nodeSize = 12;
  void AddStartFromCords(int x, int y);
  void AddTargetFromCords(int x, int y);

  void setAcceptInput(bool accept);

public slots:
  void AddStart();
  void AddTarget();
  void Clear();
  void AddMaze(QString type);
  void setType(QString str);

private:
  std::unique_ptr<DrawNodeMovable> _start;
  std::unique_ptr<DrawNodeMovable> _target;
  std::vector<DrawNode*> _obstacles;
  ObstacleWeight _obstacleType;

  const QPixmap startPixmap;
  const QPixmap targetPixmap;
  const QPixmap mountainPixmap;
  const QPixmap riverPixmap;

  bool _acceptInput;

  void setAdjustedCoords(int& startX, int& startY, int& targetX, int& targetY);
  void setAdjustedProperties(QList<QGraphicsItem*>& itemList,
                             double& weight,
                             NodeType& type);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
};

#endif // CANVAS_H
