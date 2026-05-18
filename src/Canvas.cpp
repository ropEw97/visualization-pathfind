#include "Canvas.h"
#include "DrawNode.h"
#include "DrawNodeMovable.h"
#include "Kruskal.h"
#include "Maze.h"
#include "Node.hpp"
#include "RandomMaze.h"
#include <QGraphicsSceneMouseEvent>

Canvas::Canvas(QObject* parent)
  : QGraphicsScene(parent)
  , _obstacleType(ObstacleWeight::MOUNTAIN_NODE)
  , startPixmap(
      "../17-pathfinding-algorithms-visualization/resources/star-solid.svg")
  , targetPixmap(
      "../17-pathfinding-algorithms-visualization/resources/bullseye-solid.svg")
  , mountainPixmap(
      "../17-pathfinding-algorithms-visualization/resources/mountain-solid.svg")
  , riverPixmap(
      "../17-pathfinding-algorithms-visualization/resources/water-solid.svg")
  , _acceptInput(true)
{}

void
Canvas::AddStart()
{
  if (this->_start.get() == nullptr) {
    _start = std::make_unique<DrawNodeMovable>(
      new Node(NodeType::START_NODE, 50, 350), startPixmap, width(), height());
    addItem(_start.get());
  }
}

void
Canvas::AddStartFromCords(int x, int y)
{
  if (this->_start.get() == nullptr) {
    _start = std::make_unique<DrawNodeMovable>(
      new Node(NodeType::START_NODE, x, y), startPixmap, width(), height());
    addItem(_start.get());
  }
}

void
Canvas::AddTarget()
{
  if (this->_target.get() == nullptr) {
    _target = std::make_unique<DrawNodeMovable>(
      new Node(NodeType::END_NODE, 850, 350), targetPixmap, width(), height());
    addItem(_target.get());
  }
}

void
Canvas::AddTargetFromCords(int x, int y)
{
  if (this->_target.get() == nullptr) {
    _target = std::make_unique<DrawNodeMovable>(
      new Node(NodeType::END_NODE, x, y), targetPixmap, width(), height());
    addItem(_target.get());
  }
}

void
Canvas::AddNode(const int x, const int y, const ObstacleWeight type)
{

  DrawNode* node;
  if (type == ObstacleWeight::MOUNTAIN_NODE)
    node =
      new DrawNode(new Node(NodeType::WEIGHTED_NODE,
                            static_cast<int>(ObstacleWeight::MOUNTAIN_NODE),
                            x,
                            y),
                   mountainPixmap);
  else
    node = new DrawNode(new Node(NodeType::WEIGHTED_NODE,
                                 static_cast<int>(ObstacleWeight::RIVER_NODE),
                                 x,
                                 y),
                        riverPixmap);
  if (x < 0 or x > width() - node->dim() or y < 0 or
      y > height() - node->dim()) {
    delete node;
    return;
  }
  if (_start.get()->collidesWithItem(node) or
      _target.get()->collidesWithItem(node)) {
    delete node;
    return;
  }

  for (const auto& i : _obstacles) {
    if (i->collidesWithItem(node)) {
      delete node;
      return;
    }
  }

  addItem(node);
  _obstacles.push_back(node);
}

void
Canvas::Clear()
{
  if (_start.get() != nullptr) {
    removeItem(_start.get());
    _start.release();
  }
  if (_target.get() != nullptr) {
    removeItem(_target.get());
    _target.release();
  }
  for (auto& i : _obstacles) {
    removeItem(i);
    delete i;
  }
  _obstacles.clear();
}

void
Canvas::setType(QString str)
{
  if (str == "Mountain") {
    _obstacleType = ObstacleWeight::MOUNTAIN_NODE;
  } else {
    _obstacleType = ObstacleWeight::RIVER_NODE;
  }
}

void
Canvas::AddMaze(QString type)
{
  int n = static_cast<int>(width() / DrawNode::dim(NodeType::START_NODE));
  int m = static_cast<int>(height() / DrawNode::dim(NodeType::START_NODE));
  Maze* maze;
  if (type == "Kruskal") {
    maze = new Kruskal(n, m);
  } else if (type == "Random") {
    maze = new RandomMaze(n, m);
  } else {
    return;
  }
  Clear();
  AddStartFromCords(0, 0);
  AddTargetFromCords(960, 660);
  maze->generate();
  for (const auto& p : maze->getObstacles()) {
    AddNode(p.first * DrawNode::dim(NodeType::START_NODE),
            p.second * DrawNode::dim(NodeType::START_NODE),
            ObstacleWeight::MOUNTAIN_NODE);
  }
  delete maze;
}

void
Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if (!_acceptInput)
    return;

  QGraphicsScene::mouseMoveEvent(event);
  if ((_start and !_start->isSelected()) and
      (_target and !_target->isSelected())) {
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    AddNode(x, y, _obstacleType);
  }
}

void
Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  if (!_acceptInput)
    return;

  QGraphicsScene::mouseReleaseEvent(event);
  if (event->button() == Qt::LeftButton) {
    if (_start and _start->isSelected()) {
      for (const auto& i : _obstacles) {
        if (i->collidesWithItem(_start.get())) {
          _start->setPos(_start.get()->node()->getX(),
                         _start.get()->node()->getY());
          return;
        }
      }
      _start.get()->node()->setX(_start->x());
      _start.get()->node()->setY(_start->y());
    }
    if (_target and _target->isSelected()) {
      for (const auto& i : _obstacles) {
        if (i->collidesWithItem(_target.get())) {
          _target->setPos(_target.get()->node()->getX(),
                          _target.get()->node()->getY());
          return;
        }
      }
      _target.get()->node()->setX(_target->x());
      _target.get()->node()->setY(_target->y());
    }
  }
}

void
Canvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  if (!_acceptInput)
    return;
  // qInfo() << "pos " << event->scenePos();
  if (event->button() == Qt::LeftButton) {
    std::vector<DrawNode*>::iterator iter;
    for (iter = _obstacles.begin(); iter < _obstacles.end(); iter++) {
      if (QRect((*iter)->scenePos().toPoint(), QSize(20, 20))
            .contains(event->scenePos().toPoint())) {
        removeItem(*iter);
        _obstacles.erase(iter);
        break;
      }
    }
  }
}

void
Canvas::setAcceptInput(bool accept)
{
  _acceptInput = accept;
}

DrawNodeMovable*
Canvas::getStart()
{
  return _start.get();
}

DrawNodeMovable*
Canvas::getTarget()
{
  return _target.get();
}

std::vector<DrawNode*>*
Canvas::getObstacles()
{
  return &_obstacles;
}

void
Canvas::setAdjustedCoords(int& startX, int& startY, int& targetX, int& targetY)
{
  int dim = getStart()->dim();
  int offset = (dim - Canvas::nodeSize) / 2;
  startX = getStart()->node()->getX() + offset;
  startY = getStart()->node()->getY() + offset;

  dim = getTarget()->dim();
  offset = (dim - Canvas::nodeSize) / 2;
  targetX = getTarget()->node()->getX() + offset;
  targetY = getTarget()->node()->getY() + offset;
}

void
Canvas::setAdjustedProperties(QList<QGraphicsItem*>& itemList,
                              double& weight,
                              NodeType& type)
{
  for (auto& item : itemList) {
    DrawNode* drawNode = dynamic_cast<DrawNode*>(item);
    double new_weight = drawNode->node()->getWeight();
    NodeType new_type = drawNode->node()->Type();

    if (new_type == NodeType::START_NODE && type != NodeType::END_NODE)
      type = new_type;
    if (new_type == NodeType::END_NODE)
      type = new_type;

    if (weight >= 0 && new_weight > weight)
      weight = new_weight;
    if (new_weight < 0 && new_weight < weight)
      weight = new_weight;
  }
}

Map*
Canvas::generateMap()
{
  int startX, startY, targetX, targetY;
  setAdjustedCoords(startX, startY, targetX, targetY);

  Map* map = new Map(
    startX, startY, targetX, targetY, width(), height(), Canvas::nodeSize);
  int width = map->width();
  int height = map->height();

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      Node node = map->getNode(i, j);
      std::vector<Point> vertices =
        map->getNodePolygon(node.getX(), node.getY());
      QList<QPointF> poly;
      for (auto& point : vertices)
        poly.push_back(QPointF(point.first, point.second));

      QList<QGraphicsItem*> itemList = items(QPolygonF(poly));

      if (itemList.empty())
        continue;

      double weight = node.getWeight();
      NodeType type = node.Type();

      setAdjustedProperties(itemList, weight, type);

      map->setNode(i, j, Node(type, weight, node.getX(), node.getY()));
    }
  }

  return map;
}
