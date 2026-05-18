#define CATCH_CONFIG_MAIN
#include "../catch.hpp"


#include "mapCreating.h"
#include "BreadthFirstSearch.h"
#include "Astar.h"



TEST_CASE("BreadthFirstSearch", "[class]")
{
    SECTION("Ako su prepreke postavljene tako da sa svih strana okruzuju startni cvor pa nije moguce pronaci put od starta do cilja, metod shortestPathFinder vratice prazan vektor")
    {
	Map* ulaz = createMap({{7,10}, {7,11}, {7,12}, {8,10}, {9, 11}, {8,12}});

	BreadthFirstSearch bfs(ulaz);
	std::vector<Node> izlaz = bfs.pathFinder(ulaz);
	izlaz = bfs.shortestPathFinder();
	delete ulaz;

        REQUIRE(izlaz.empty());
    }

    SECTION("Ako su prepreke postavljene tako da sa svih strana okruzuju ciljni cvor pa nije moguce pronaci put od starta do cilja, metod shortestPathFinder vratice prazan vektor")
    {
	Map* ulaz = createMap({{25,32}, {25,33}, {25,34}, {26,32}, {27, 33}, {26,34}});

	BreadthFirstSearch bfs(ulaz);
	std::vector<Node> izlaz =  bfs.pathFinder(ulaz);
	izlaz = bfs.shortestPathFinder();
	delete ulaz;
        REQUIRE(izlaz.empty());
    }


    SECTION("Tokom BFS pretrage bice obidjen veci broj cvorova nego tokom pretrage algoritmom A*")
    {
        Map* ulaz = createMap({{0,0}, {0,1}, {10,18}, {11,18}, {12, 17}, {12,16}});

	BreadthFirstSearch bfs(ulaz);
	std::vector<Node> izlazBfs = bfs.pathFinder(ulaz);

	Astar astar(ulaz);
	std::vector<Node> izlazAstar = astar.pathFinder(ulaz);
	delete ulaz;
        REQUIRE(izlazBfs.size() > izlazAstar.size());
    }

    SECTION("Metod shortestPathFinder ce uvek vratiti isti put pri svakom pokretanju BFS algoritma")
    {
    Map* ulaz = createMap({{0,0}, {0,1}, {10,18}, {11,18}, {12, 17}, {12,16}});

	BreadthFirstSearch bfs1(ulaz);
	std::vector<Node> izlaz1 = bfs1.pathFinder(ulaz);
	izlaz1 = bfs1.shortestPathFinder();

	BreadthFirstSearch bfs2(ulaz);
	std::vector<Node> izlaz2 = bfs2.pathFinder(ulaz);
	izlaz2 = bfs2.shortestPathFinder();
	bool condition = true;

	if(izlaz1.size() != izlaz2.size()){
		condition = false;
	}
	else{
		for(uint i=0; i<izlaz1.size(); i++){
			if(izlaz1[i] != izlaz2[i])
			{
				condition = false;
				break;
			}
		}
	}
	delete ulaz;
        REQUIRE(condition);
    }

    SECTION("Ako su start i cilj isto pozicionirani, metod pathFinder vratice vektor u kome se nalazi samo ciljni cvor")
    {
        Map* map = new Map(298, 316, 298, 316, 400, 400, 12);
    	std::pair<int,int>indices = map->getIndices(298,316);
    	int endi = indices.first, endj = indices.second;
    	Node end = map->getNode(endi, endj);
    	map->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));
  
	Node ocekivaniIzlaz = map->getEndNode();

	BreadthFirstSearch bfs(map);
	std::vector<Node> izlaz = bfs.pathFinder(map);

	bool condition = true;

	if(izlaz.size() != 1)
		condition = false;
	else{
		if(izlaz[0] != ocekivaniIzlaz)
			condition = false;
	}
	delete map;
        REQUIRE(condition);
    }

    SECTION("Ako su start i cilj isto pozicionirani, metod shortestPathFinder vratice vektor u kome se nalazi samo ciljni cvor")
    {
        
	Map* map = new Map(298, 316, 298, 316, 400, 400, 12);
    	std::pair<int,int>indices = map->getIndices(298,316);
    	int endi = indices.first, endj = indices.second;
    	Node end = map->getNode(endi, endj);
    	map->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));
  
	Node ocekivaniIzlaz = map->getEndNode();

	BreadthFirstSearch bfs(map);
	std::vector<Node> izlaz = bfs.pathFinder(map);
	izlaz = bfs.shortestPathFinder();
	bool condition = true;

	if(izlaz.size() != 1)
		condition = false;
	else{
		if(izlaz[0] != ocekivaniIzlaz)
			condition = false;
	}
		delete map;
        REQUIRE(condition);
    }
}


TEST_CASE("Astar", "[class]")
{
    SECTION("Ako su prepreke postavljene tako da sa svih strana okruzuju startni cvor pa nije moguce pronaci put od starta do cilja, metod shortestPathFinder vratice prazan vektor")
    {
        
	Map* ulaz = createMap({{7,10}, {7,11}, {7,12}, {8,10}, {9, 11}, {8,12}});

	Astar astar(ulaz);
	std::vector<Node> izlaz = astar.pathFinder(ulaz);
	izlaz = astar.shortestPathFinder();
	delete ulaz;
        REQUIRE(izlaz.empty());
    }

    SECTION("Ako su prepreke postavljene tako da sa svih strana okruzuju ciljni cvor pa nije moguce pronaci put od starta do cilja, metod shortestPathFinder vratice prazan vektor")
    {
	Map* ulaz = createMap({{25,32}, {25,33}, {25,34}, {26,32}, {27, 33}, {26,34}});

	Astar astar(ulaz);
	std::vector<Node> izlaz = astar.pathFinder(ulaz);
	izlaz = astar.shortestPathFinder();
	delete ulaz;
        REQUIRE(izlaz.empty());
    }

    SECTION("Ako su start i cilj isto pozicionirani, metod pathFinder vratice vektor u kome se nalazi samo ciljni cvor")
    {
        Map* map = new Map(298, 316, 298, 316, 400, 400, 12);
    	std::pair<int,int>indices = map->getIndices(298,316);
    	int endi = indices.first, endj = indices.second;
    	Node end = map->getNode(endi, endj);
    	map->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));
  
	Node ocekivaniIzlaz = map->getEndNode();

	Astar astar(map);
	std::vector<Node> izlaz = astar.pathFinder(map);

	bool condition = true;

	if(izlaz.size() != 1)
		condition = false;
	else{
		if(izlaz[0] != ocekivaniIzlaz)
			condition = false;
	}
	delete map;
        REQUIRE(condition);
    }

    SECTION("Ako su start i cilj isto pozicionirani, metod shortestPathFinder vratice vektor u kome se nalazi samo ciljni cvor")
    {
        
	Map* map = new Map(298, 316, 298, 316, 400, 400, 12);
    	std::pair<int,int>indices = map->getIndices(298,316);
    	int endi = indices.first, endj = indices.second;
    	Node end = map->getNode(endi, endj);
    	map->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));
  
	Node ocekivaniIzlaz = map->getEndNode();

	Astar astar(map);
	std::vector<Node> izlaz = astar.pathFinder(map);
	izlaz = astar.shortestPathFinder();
	bool condition = true;

	if(izlaz.size() != 1)
		condition = false;
	else{
		if(izlaz[0] != ocekivaniIzlaz)
			condition = false;
	}
		delete map;
        REQUIRE(condition);
    }

    SECTION("Metod heuristic vratice vrednost 0 kao Menhetn rastojanje od ciljnog cvora")
    {
     	Map* ulaz = createMap({{0,0}, {0,1}, {10,18}, {11,18}, {12, 17}, {12,16}});

	Astar astar(ulaz);
	double ocekivaniIzlaz = 0;

	Node endNode = ulaz->getEndNode();
	double izlaz = astar.heuristic(endNode, endNode);
	delete ulaz;
        REQUIRE(izlaz == ocekivaniIzlaz);
    }
}
