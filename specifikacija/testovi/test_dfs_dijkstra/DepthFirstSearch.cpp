#include "DepthFirstSearch.h"
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <iterator>
#include <algorithm>

std::vector<Node> DepthFirstSearch::pathFinder(Map* mapStart){
    Node startNode = mapStart->getStartNode();
    Node endNode;

    std::set<Node> visited;
    std::vector<Node> path;

    std::stack<Node> stek;
    stek.push(startNode);

    std::map<Node, Node> parent;

    while(!stek.empty()){
        Node s = stek.top();
        stek.pop();

        if (visited.find(s) == visited.end()){
            path.push_back(s);
            visited.insert(s);
             if(s.Type() == NodeType::END_NODE){
                 endNode = s;
                 pathIsFound = true;
                 break;
             }
        }
        for (Node nextNode : mapStart->getAdjacentNodes(s))
            if (visited.find(nextNode) == visited.end()){
                stek.push(nextNode);
                parent[nextNode] = s;
             }
    }

    if (pathIsFound)
    {
    Node curr = endNode;
    while(curr != startNode){
        _shortest.push_back(curr);
        curr = parent[curr];
    }
    _shortest.push_back(curr);
    }

    std::reverse(_shortest.begin(), _shortest.end());

    return path;
}
