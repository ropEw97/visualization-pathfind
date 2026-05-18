#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Canvas.h"
#include <QFileDialog>
#include <QMessageBox>

using FileEntry = std::tuple<QString, int, int>;

class MapLoader : public QObject
{
  Q_OBJECT

public:
  MapLoader(Canvas* canvas);

public slots:
  void saveMap();
  void loadMap();

private:
  Canvas* m_canvas;

  QHash<NodeType, QString> m_types;
  QHash<ObstacleWeight, QString> m_weights;

  QString getFilename(bool saving);
  void write(QTextStream& out);
  bool read(QTextStream& in, std::vector<FileEntry>& items);
  void addToMap(std::vector<FileEntry>& items);
  void showMessage(const QString& msg) const;
  ObstacleWeight getWeightType(DrawNode* node);
};

#endif // MAPLOADER_H
