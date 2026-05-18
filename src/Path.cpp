#include "Path.h"
#include <QPainter>
#include <QTimer>

static const QColor FINAL_PATH_COLOR = QColor::fromRgb(100, 0, 0);
static const QColor WORKING_PATH_COLOR = QColor::fromRgb(0, 100, 0);

Path::Path(const std::vector<Node>& path,
           PathType type,
           int speed,
           int index,
           QGraphicsItem* parent)
  : QGraphicsObject(parent)
  , m_index(index)
  , m_type(type)
  , m_speed(speed)
{
  m_path = {};
  for (const Node& node : path)
    m_path.emplace_back(node.getX(), node.getY());

  setPos(0, 0);
  m_nodeSize = Canvas::nodeSize;

  if (m_type == PathType::FINAL_PATH)
    setZValue(100);
}

QRectF
Path::boundingRect() const
{
  return QRectF(0, 0, 1000, 700);
}

void
Path::paint(QPainter* painter,
            const QStyleOptionGraphicsItem* option,
            QWidget* widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)

  painter->setPen(getColor());
  painter->setBrush(getColor());

  for (unsigned i = 0; i < m_index; i++) {
    QVector<QPointF> points = { { 0, 0.5 * m_nodeSize },
                                { 0.25 * m_nodeSize, 0 },
                                { 0.75 * m_nodeSize, 0 },
                                { 1.0 * m_nodeSize, 0.5 * m_nodeSize },
                                { 0.75 * m_nodeSize, 1.0 * m_nodeSize },
                                { 0.25 * m_nodeSize, 1.0 * m_nodeSize },
                                { 0, 0.5 * m_nodeSize } };
    for (auto& point : points)
      point += QPointF(m_path[i].first, m_path[i].second);

    painter->drawPolygon(points);
  }
}

void
Path::drawNext()
{
  if (m_index < m_path.size()) {
    m_index++;
    update();
    QTimer::singleShot(m_speed, this, &Path::drawNext);
  } else {
    emit pathFinishedDrawing(m_type);
  }
}

QColor
Path::getColor() const
{
  if (m_type == PathType::FINAL_PATH)
    return FINAL_PATH_COLOR;
  return WORKING_PATH_COLOR;
}
