#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MapLoader.h"
#include <QComboBox>
#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

public slots:
  void AlgorithmSelected();
  void EnableAlgorithms();
  void SaveScreenshot();

private:
  Ui::MainWindow* ui;
  QGraphicsScene* _canvas;
  MapLoader* _mapLoader;
};
#endif // MAINWINDOW_H

void
SetComboBoxItemEnabled(QComboBox* comboBox, int index, bool enabled);
