QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Astar.cpp \
    src/BreadthFirstSearch.cpp \
    src/Canvas.cpp \
    src/DepthFirstSearch.cpp \
    src/Dijkstra.cpp \
    src/DrawNode.cpp \
    src/DrawNodeMovable.cpp \
    src/Kruskal.cpp \
    src/MainWindow.cpp \
    src/Map.cpp \
    src/MapLoader.cpp \
    src/Maze.cpp \
    src/Node.cpp \
    src/Path.cpp \
    src/PathFindingAlgorithm.cpp \
    src/RandomMaze.cpp \
    src/main.cpp

HEADERS += \
    src/Astar.h \
    src/BreadthFirstSearch.h \
    src/Canvas.h \
    src/DepthFirstSearch.h \
    src/Dijkstra.h \
    src/DrawNode.h \
    src/DrawNodeMovable.h \
    src/Kruskal.h \
    src/MainWindow.h \
    src/Map.h \
    src/MapLoader.h \
    src/Maze.h \
    src/Node.hpp \
    src/Path.h \
    src/PathFindingAlgorithm.h \
    src/RandomMaze.h

FORMS += \
    src/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
