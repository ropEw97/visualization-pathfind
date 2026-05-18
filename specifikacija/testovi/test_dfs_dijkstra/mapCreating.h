#ifndef MAP_CREATING_H
#define MAP_CREATING_H

#include "Map.h"

Map* createMap(const std::vector<std::pair<int, int>>& obstacleIdxs)
{
    Map* map = new Map(100, 100, 298, 316, 400, 400, 12);
    std::pair<int,int>indices = map->getIndices(298,316);
    int endi = indices.first, endj = indices.second;
    Node end = map->getNode(endi, endj);
    map->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));

    for (auto &idx : obstacleIdxs)
    {
        Node n = map->getNode(idx.first,idx.second);
        map->setNode(idx.first,idx.second, Node(
                         n.Type(),
                         static_cast<double>(ObstacleWeight::MOUNTAIN_NODE),
                         n.getX(),n.getY()));
    }

    return map;

}


#endif