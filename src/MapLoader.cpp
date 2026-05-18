#include "MapLoader.h"

MapLoader::MapLoader(Canvas* canvas)
  : QObject()
  , m_canvas(canvas)
{
  m_types[NodeType::START_NODE] = "s";
  m_types[NodeType::END_NODE] = "t";
  m_weights[ObstacleWeight::MOUNTAIN_NODE] = "m";
  m_weights[ObstacleWeight::RIVER_NODE] = "r";
}

QString
MapLoader::getFilename(bool saving)
{
  QString path = QDir::currentPath() + QDir::separator() + "maps";
  QDir dir(QDir::currentPath());
  if (!dir.exists("maps"))
    path = QDir::currentPath();

  QString filename;

  if (saving) {
    filename = QFileDialog::getSaveFileName(nullptr, "Save as", path);
  } else {
    filename = QFileDialog::getOpenFileName(nullptr, "Open map", path);
  }

  return filename;
}

ObstacleWeight
MapLoader::getWeightType(DrawNode* drawNode)
{
  double weight = drawNode->node()->getWeight();
  ObstacleWeight weightType = ObstacleWeight::MOUNTAIN_NODE;
  auto weightTypes = m_weights.keys();
  for (ObstacleWeight& w : weightTypes) {
    if (static_cast<int>(w) == weight) {
      weightType = w;
      break;
    }
  }

  return weightType;
}

void
MapLoader::write(QTextStream& out)
{
  DrawNodeMovable* start = m_canvas->getStart();
  DrawNodeMovable* target = m_canvas->getTarget();

  out << m_types[NodeType::START_NODE] << " " << start->node()->getX() << " "
      << start->node()->getY() << Qt::endl;

  out << m_types[NodeType::END_NODE] << " " << target->node()->getX() << " "
      << target->node()->getY() << Qt::endl;

  auto obstacles = m_canvas->getObstacles();
  for (DrawNode* drawNode : *obstacles) {
    out << m_weights[getWeightType(drawNode)] << " " << drawNode->node()->getX()
        << " " << drawNode->node()->getY() << Qt::endl;
  }
}

bool
MapLoader::read(QTextStream& in, std::vector<FileEntry>& items)
{
  bool success = true;

  while (!in.atEnd()) {
    QString line = in.readLine();
    QList<QString> lineSplit = line.split(" ");
    if (lineSplit.size() != 3) {
      success = false;
      break;
    }

    auto typeNames = m_types.values();
    auto weightNames = m_weights.values();
    if (typeNames.indexOf(lineSplit[0]) == -1 &&
        weightNames.indexOf(lineSplit[0]) == -1)
      success = false;

    bool xOk, yOk;
    int x, y;
    x = lineSplit[1].toInt(&xOk);
    y = lineSplit[2].toInt(&yOk);
    if (!(xOk && yOk))
      success = false;

    if (!success)
      break;

    items.emplace_back(lineSplit[0], x, y);
  }

  return success;
}

void
MapLoader::addToMap(std::vector<FileEntry>& items)
{
  m_canvas->Clear();
  m_canvas->AddStartFromCords(std::get<1>(items[0]), std::get<2>(items[0]));
  m_canvas->AddTargetFromCords(std::get<1>(items[1]), std::get<2>(items[1]));

  for (unsigned i = 2; i < items.size(); i++) {
    auto weightTypes = m_weights.keys(std::get<0>(items[i]));
    m_canvas->AddNode(
      std::get<1>(items[i]), std::get<2>(items[i]), weightTypes[0]);
  }
}

void
MapLoader::saveMap()
{
  if (m_canvas->getStart() == nullptr || m_canvas->getTarget() == nullptr) {
    showMessage("Add start and target.");
    return;
  }

  QString filename = getFilename(true);
  if (filename == nullptr)
    return;

  QFile file(filename);
  if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
    showMessage("Writing to file failed.");
    return;
  }

  QTextStream out(&file);
  write(out);

  file.close();
}

void
MapLoader::loadMap()
{
  QString filename = getFilename(false);
  if (filename == nullptr)
    return;

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    showMessage("Reading from file failed.");
    return;
  }

  std::vector<FileEntry> items;
  QTextStream in(&file);

  bool success = read(in, items);

  file.close();

  if (!success || std::get<0>(items[0]) != m_types[NodeType::START_NODE] ||
      std::get<0>(items[1]) != m_types[NodeType::END_NODE]) {
    showMessage("Invalid map file.");
    return;
  }

  addToMap(items);
}

void
MapLoader::showMessage(const QString& msg) const
{
  QMessageBox msgBox;
  msgBox.setText(msg);
  msgBox.setWindowTitle("Warning");
  msgBox.exec();
}
