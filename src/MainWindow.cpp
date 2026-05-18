#include "MainWindow.h"
#include "Astar.h"
#include "BreadthFirstSearch.h"
#include "Canvas.h"
#include "DepthFirstSearch.h"
#include "Dijkstra.h"
#include "Map.h"
#include "Node.hpp"
#include "Path.h"
#include "PathFindingAlgorithm.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <algorithm>

#define CANVAS_WIDTH 990
#define CANVAS_HEIGHT 690

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , _canvas(new Canvas(this))
  , _mapLoader(new MapLoader(dynamic_cast<Canvas*>(_canvas)))
{
  ui->setupUi(this);
  ui->gvCanvas->setFixedSize(CANVAS_WIDTH, CANVAS_HEIGHT);
  _canvas->setSceneRect(ui->gvCanvas->rect());
  ui->gvCanvas->setScene(_canvas);
  ui->gvCanvas->setRenderHint(QPainter::Antialiasing);
  ui->gvCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  ui->gvCanvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->gvCanvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  SetComboBoxItemEnabled(ui->cbMaze, 0, false);
  SetComboBoxItemEnabled(ui->cbAlgorithm, 0, false);

  connect(ui->pbStart,
          &QPushButton::clicked,
          dynamic_cast<Canvas*>(_canvas),
          &Canvas::AddStart);
  connect(ui->pbTarget,
          &QPushButton::clicked,
          dynamic_cast<Canvas*>(_canvas),
          &Canvas::AddTarget);
  connect(ui->pbClear,
          &QPushButton::clicked,
          dynamic_cast<Canvas*>(_canvas),
          &Canvas::Clear);
  connect(ui->pbGenMaze, &QPushButton::clicked, [this]() {
    dynamic_cast<Canvas*>(this->_canvas)
      ->AddMaze(this->ui->cbMaze->currentText());
  });
  connect(ui->cbObstacle,
          &QComboBox::currentTextChanged,
          dynamic_cast<Canvas*>(_canvas),
          &Canvas::setType);

  connect(ui->pbStartAlgorithm,
          &QPushButton::clicked,
          this,
          &MainWindow::AlgorithmSelected);
  connect(
    ui->pbClear, &QPushButton::clicked, this, &MainWindow::EnableAlgorithms);

  connect(ui->pbSave, &QPushButton::clicked, _mapLoader, &MapLoader::saveMap);
  connect(ui->pbLoad, &QPushButton::clicked, _mapLoader, &MapLoader::loadMap);
  connect(
    ui->pbScreenShot, &QPushButton::clicked, this, &MainWindow::SaveScreenshot);

  connect(ui->pbClearPath,
          &QPushButton::clicked,
          this,
          &MainWindow::EnableAlgorithms);
}

MainWindow::~MainWindow()
{
  delete ui;
  delete _mapLoader;
}

void
MainWindow::AlgorithmSelected()
{
  if (!dynamic_cast<Canvas*>(_canvas)->getStart() ||
      !dynamic_cast<Canvas*>(_canvas)->getTarget())
    return;

  if (ui->cbAlgorithm->currentIndex() == 0)
    return;

  ui->cbAlgorithm->setDisabled(true);
  ui->cbMaze->setDisabled(true);
  ui->cbObstacle->setDisabled(true);
  ui->pbStart->setDisabled(true);
  ui->pbTarget->setDisabled(true);
  ui->pbSave->setDisabled(true);
  ui->pbLoad->setDisabled(true);
  ui->pbStartAlgorithm->setDisabled(true);
  ui->pbGenMaze->setDisabled(true);
  dynamic_cast<Canvas*>(_canvas)->setAcceptInput(false);

  QComboBox* alg = MainWindow::findChild<QComboBox*>("cbAlgorithm");

  Map* mapa = dynamic_cast<Canvas*>(_canvas)->generateMap();

  std::vector<Node> path;
  std::vector<Node> shortestPath;

  if (alg->currentIndex() == 1) { // dfs
    DepthFirstSearch dfs(mapa);
    path = dfs.pathFinder(mapa);
    shortestPath = dfs.shortestPathFinder();

  } else if (alg->currentIndex() == 2) { // bfs
    BreadthFirstSearch bfs(mapa);
    path = bfs.pathFinder(mapa);
    shortestPath = bfs.shortestPathFinder();

  } else if (alg->currentIndex() == 3) { // dijkstra
    Dijkstra dijk(mapa);
    path = dijk.pathFinder(mapa);
    shortestPath = dijk.shortestPathFinder();

  } else if (alg->currentIndex() == 4) { // astar
    Astar astar(mapa);
    path = astar.pathFinder(mapa);
    shortestPath = astar.shortestPathFinder();
  }

  Path* staza = new Path(path, PathType::WORKING_PATH, 10, 0, nullptr);
  _canvas->addItem(staza);
  connect(ui->pbClear, &QPushButton::clicked, staza, &Path::deleteLater);
  connect(ui->pbClearPath, &QPushButton::clicked, staza, &Path::deleteLater);

  Path* najkracaStaza =
    new Path(shortestPath, PathType::FINAL_PATH, 10, 0, nullptr);
  _canvas->addItem(najkracaStaza);
  connect(
    ui->pbClear, &QPushButton::clicked, najkracaStaza, &Path::deleteLater);
  connect(
    ui->pbClearPath, &QPushButton::clicked, najkracaStaza, &Path::deleteLater);

  connect(staza, &Path::pathFinishedDrawing, [najkracaStaza]() {
    najkracaStaza->drawNext();
  });
  connect(najkracaStaza, &Path::pathFinishedDrawing, [this]() {
    this->ui->pbScreenShot->setEnabled(true);
  });
  staza->drawNext();

  delete mapa;
}

void
MainWindow::EnableAlgorithms()
{
  ui->cbAlgorithm->setEnabled(true);
  ui->cbMaze->setEnabled(true);
  ui->cbObstacle->setEnabled(true);
  ui->pbStart->setEnabled(true);
  ui->pbTarget->setEnabled(true);
  ui->pbSave->setEnabled(true);
  ui->pbLoad->setEnabled(true);
  ui->pbStartAlgorithm->setEnabled(true);
  ui->pbGenMaze->setEnabled(true);

  ui->pbScreenShot->setDisabled(true);

  dynamic_cast<Canvas*>(_canvas)->setAcceptInput(true);
}

void
SetComboBoxItemEnabled(QComboBox* comboBox, int index, bool enabled)
{
  auto* model = qobject_cast<QStandardItemModel*>(comboBox->model());
  assert(model);
  if (!model)
    return;

  auto* item = model->item(index);
  assert(item);
  if (!item)
    return;
  item->setEnabled(enabled);
}

void
MainWindow::SaveScreenshot()
{
  QString path = QDir::currentPath();
  QString filename;
  filename =
    QFileDialog::getSaveFileName(nullptr, "Save as", path, "Image (*.png)");
  if (filename == nullptr)
    return;

  QPixmap img = ui->gvCanvas->grab();
  img.save(filename);
}
