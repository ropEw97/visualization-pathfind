#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "mapCreating.h"
#include "DepthFirstSearch.h"
#include "Dijkstra.h"


TEST_CASE("DepthFirstSearch", "[class]")
{
    SECTION("Ako su prepreke postavljene tako da sa svih strana okruzuju startni cvor pa nije moguce pronaci put od starta do cilja, metod shortestPathFinder vratice prazan vektor")
    {
        
	Map* ulaz = createMap({{7,10}, {7,11}, {7,12}, {8,10}, {9, 11}, {8,12}});

	DepthFirstSearch dfs(ulaz);
    std::vector<Node> izlaz = dfs.pathFinder(ulaz);
	izlaz = dfs.shortestPathFinder();
	delete ulaz;

        REQUIRE(izlaz.empty());
    }

    SECTION("Ako su prepreke postavljene tako da sa svih strana okruzuju ciljni cvor pa nije moguce pronaci put od starta do cilja, metod shortestPathFinder vratice prazan vektor")
    {
	Map* ulaz = createMap({{25,32}, {25,33}, {25,34}, {26,32}, {27, 33}, {26,34}});

	DepthFirstSearch dfs(ulaz);
	std::vector<Node> izlaz = dfs.pathFinder(ulaz);
	izlaz = dfs.shortestPathFinder();
	delete ulaz;
        REQUIRE(izlaz.empty());
    }

    SECTION("Metod shortestPathFinder ce uvek vratiti isti put pri svakom pokretanju DFS algoritma")
    {
        
    Map* ulaz = createMap({{0,0}, {0,1}, {10,18}, {11,18}, {12, 17}, {12,16}});

	DepthFirstSearch dfs1(ulaz);
	std::vector<Node> izlaz1 = dfs1.pathFinder(ulaz);
	izlaz1 = dfs1.shortestPathFinder();

	DepthFirstSearch dfs2(ulaz);
	std::vector<Node> izlaz2 = dfs2.pathFinder(ulaz);
	izlaz2 = dfs2.shortestPathFinder();

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
        Map* mapa = new Map(298, 316, 298, 316, 400, 400, 12);
    	std::pair<int,int>indices = mapa->getIndices(298,316);
    	int endi = indices.first, endj = indices.second;
    	Node end = mapa->getNode(endi, endj);
    	mapa->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));
  
	Node ocekivaniIzlaz = mapa->getEndNode();

	DepthFirstSearch dfs(mapa);
	std::vector<Node> izlaz = dfs.pathFinder(mapa);

	bool condition = true;

	if(izlaz.size() != 1)
		condition = false;
	else{
		if(izlaz[0] != ocekivaniIzlaz)
			condition = false;
	}
	delete mapa;
        REQUIRE(condition);
    }

    SECTION("Ako su start i cilj isto pozicionirani, metod shortestPathFinder vratice vektor u kome se nalazi samo ciljni cvor")
    {
        
	Map* mapa = new Map(298, 316, 298, 316, 400, 400, 12);
    	std::pair<int,int>indices = mapa->getIndices(298,316);
    	int endi = indices.first, endj = indices.second;
    	Node end = mapa->getNode(endi, endj);
    	mapa->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));
  
	Node ocekivaniIzlaz = mapa->getEndNode();

	DepthFirstSearch dfs(mapa);
	std::vector<Node> izlaz = dfs.pathFinder(mapa);
	izlaz = dfs.shortestPathFinder();

	bool condition = true;

	if(izlaz.size() != 1)
		condition = false;
	else{
		if(izlaz[0] != ocekivaniIzlaz)
			condition = false;
	}
		delete mapa;
        REQUIRE(condition);
    }
}


TEST_CASE("Dijkstra", "[class]")
{
    SECTION("Ako su prepreke postavljene tako da sa svih strana okruzuju startni cvor pa nije moguce pronaci put od starta do cilja, metod shortestPathFinder vratice prazan vektor")
    {

	Map* ulaz = createMap({{7,10}, {7,11}, {7,12}, {8,10}, {9, 11}, {8,12}});

	Dijkstra dijkstra(ulaz);
	std::vector<Node> izlaz = dijkstra.pathFinder(ulaz);
	izlaz = dijkstra.shortestPathFinder();
	delete ulaz;
        REQUIRE(izlaz.empty());
    }

    SECTION("Ako su prepreke postavljene tako da sa svih strana okruzuju ciljni cvor pa nije moguce pronaci put od starta do cilja, metod shortestPathFinder vratice prazan vektor")
    {

	Map* ulaz = createMap({{25,32}, {25,33}, {25,34}, {26,32}, {27, 33}, {26,34}});

	Dijkstra dijkstra(ulaz);
	std::vector<Node> izlaz = dijkstra.pathFinder(ulaz);
	izlaz = dijkstra.shortestPathFinder();
	delete ulaz;
        REQUIRE(izlaz.empty());
    }

    SECTION("Ako su start i cilj isto pozicionirani, metod pathFinder vratice vektor u kome se nalazi samo ciljni cvor")
    {
        Map* mapa = new Map(298, 316, 298, 316, 400, 400, 12);
    	std::pair<int,int>indices = mapa->getIndices(298,316);
    	int endi = indices.first, endj = indices.second;
    	Node end = mapa->getNode(endi, endj);
    	mapa->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));
  
	Node ocekivaniIzlaz = mapa->getEndNode();

	Dijkstra dijkstra(mapa);
	std::vector<Node> izlaz = dijkstra.pathFinder(mapa);

	bool condition = true;

	if(izlaz.size() != 1)
		condition = false;
	else{
		if(izlaz[0] != ocekivaniIzlaz)
			condition = false;
	}
	delete mapa;
        REQUIRE(condition);
    }

    SECTION("Ako su start i cilj isto pozicionirani, metod shortestPathFinder vratice vektor u kome se nalazi samo ciljni cvor")
    {
        
	Map* mapa = new Map(298, 316, 298, 316, 400, 400, 12);
    	std::pair<int,int>indices = mapa->getIndices(298,316);
    	int endi = indices.first, endj = indices.second;
    	Node end = mapa->getNode(endi, endj);
    	mapa->setNode(endi,endj, Node(NodeType::END_NODE,
                                 end.getX(),
                                 end.getY()));
  
	Node ocekivaniIzlaz = mapa->getEndNode();

	Dijkstra dijkstra(mapa);
	std::vector<Node> izlaz = dijkstra.pathFinder(mapa);
	izlaz = dijkstra.shortestPathFinder();
	bool condition = true;

	if(izlaz.size() != 1)
		condition = false;
	else{
		if(izlaz[0] != ocekivaniIzlaz)
			condition = false;
	}
		delete mapa;
        REQUIRE(condition);
    }

}
