#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "Node.hpp"
#include "Map.h"



TEST_CASE("Node", "[class]")
{
    SECTION("Konstruktor postavlja unutrasnja polja, a geteri\
    vracaju tacne vrednosti")
    {
        int x = 100, y = 100;
        double weight = 34.5;
        NodeType type = NodeType::WEIGHTED_NODE;
        Node a;
        bool condition;

        a = Node(type, weight, x, y);
        condition = a.getX() == x && a.getY() == y
                    && a.getWeight() == weight && a.Type() == type;

        REQUIRE(condition);
    }


    SECTION("Podrazumevani konstruktor postavlja koordinate\
    na 0,0 i tezinu na 1")
    {
        Node a;
        bool condition;

        a = Node();
        condition = a.getX() == 0 && a.getY() == 0
                    && a.getWeight() == 1;

        REQUIRE(condition);
    }


    SECTION("Cvorovi se racunaju kao jednaki ako imaju\
    iste koordinate")
    {
        Node a, b;

        a = Node(NodeType::WEIGHTED_NODE, 43, 56, 67);
        b = Node(NodeType::END_NODE, 56, 67);

        REQUIRE(a == b);
    }

    SECTION("Cvorovi se uredjuju prvo po x, pa po y koordinati")
    {
        Node a, b, c;
        std::vector<Node> vec;
        bool condition;

        a = Node(NodeType::WEIGHTED_NODE, 1, 2);
        b = Node(NodeType::WEIGHTED_NODE, 2, 3);
        c = Node(NodeType::WEIGHTED_NODE, 2, 2);
        vec.push_back(a);
        vec.push_back(b);
        vec.push_back(c);
        std::sort(vec.begin(), vec.end());
        
        condition = a == vec[0] && b == vec[2] && c == vec[1];

        REQUIRE(condition);
    }

}


TEST_CASE("Map", "[class]")
{
    SECTION("Mapa je inicijalizovana tako da sadrzi width() kolona,\
    i height() vrsta popunjenih cvorovima tipa WEIGHTED")
    {
        Map map = Map(100, 100, 200, 200, 400, 400, 12);
        bool allWeighted = true;

        for (uint i = 0; i < map.height(); i++)
        {
            for (uint j = 0; j < map.width(); j++)
            {
                Node node = map.getNode(i, j);
                if (node.Type() != NodeType::WEIGHTED_NODE)
                    allWeighted = false;
            }
        }

        REQUIRE(allWeighted);
    }


    SECTION("Mapa je konstruisana tako da se koordinate jednog \
    polja poklapaju sa prosledjenim koordinatama pocetka, tj \
    mapa je poravnata sa pocetkom")
    {
        int startX = 100, startY = 100;
        Map map = Map(startX, startY, 200, 200, 400, 400, 12);
        bool aligned = false;

        for (uint i = 0; i < map.height(); i++)
        {
            for (uint j = 0; j < map.width(); j++)
            {
                Node node = map.getNode(i, j);
                if (node.getX() == startX && node.getY() == startY)
                    aligned = true;
            }
        }

        REQUIRE(aligned);
    }


    SECTION("Velicina polja mora biti deljiva sa 4, za sta ce \
    se pobrinuti konstruktor")
    {
        Map map1 = Map(100, 100, 200, 200, 400, 400, 12);
        Map map2 = Map(100, 100, 200, 200, 400, 400, 14);
        bool equal = true;

        for (uint i = 0; i < map1.height(); i++)
        {
            for (uint j = 0; j < map1.width(); j++)
            {
                Node node1 = map1.getNode(i, j);
                Node node2 = map2.getNode(i, j);
                if (!(node1 == node2))
                    equal = false;
            }
        }

        REQUIRE(equal);
    }

    SECTION("Metod getStartNode() vraca onaj cvor cije se koordinate\
    poklapaju sa prosledjenim koordinatama pocetka")
    {
        int startX = 100, startY = 100;
        Map map = Map(startX, startY, 200, 200, 400, 400, 12);
        bool condition;

        Node start = map.getStartNode();
        condition = start.getX() == startX && start.getY() == startY;

        REQUIRE(condition);
    }

    SECTION("Metod getEndNode() vraca onaj cvor cije se koordinate\
    poklapaju sa prosledjenim koordinatama cilja (iako se ovaj\
    cvor ne mora nalaziti u mapi, ako nisu prosledjene medjusobno\
     poravnate koordinate za pocetak i cilj)")
    {
        int endX = 200, endY = 200;
        Map map = Map(100, 100, endX, endY, 400, 400, 12);
        bool condition;

        Node end = map.getEndNode();
        condition = end.getX() == endX && end.getY() == endY;

        REQUIRE(condition);
    }

    SECTION("Metod setNode() postavlja cvor sa zadatim indeksima na\
    prosledjeni cvor, a getNode() vraca cvor sa datim indeksima")
    {
        Map map = Map(100, 100, 200, 200, 400, 400, 12);
        Node oldNode;
        double newWeight = 1000;

        oldNode = map.getNode(1, 2);
        map.setNode(1, 2, Node(oldNode.Type(),
                                newWeight,
                                oldNode.getX(),
                                oldNode.getY()));

        REQUIRE(map.getNode(1, 2).getWeight() == newWeight);
    }

    SECTION("Metod setNode() ne radi nista ukoliko su indeksi\
     izvan opsega")
    {
        Map map = Map(100, 100, 200, 200, 400, 400, 12);
        Node oldNode;
        double newWeight = 1000;

        oldNode = map.getNode(1, 2);
        map.setNode(6000, 3452, Node(oldNode.Type(),
                                newWeight,
                                oldNode.getX(),
                                oldNode.getY()));

        REQUIRE(map.getNode(1, 2).getWeight() != newWeight);
    }

    SECTION("Metod getNode() vraca podrazumevanu vrednost za cvor\
    ako su indeksi van opsega")
    {
        Map map = Map(100, 100, 200, 200, 400, 400, 12);
        Node defaultNode = Node();
        Node node;

        node = map.getNode(24123, 45);

        REQUIRE(node == defaultNode);
    }

    SECTION("Unutrasnji cvorovi imaju po 6 suseda")
    {
        Map map = Map(100, 100, 200, 200, 400, 400, 12);
        Node node;
        std::vector<Node> neighbors;

        node = map.getNode(4, 6);
        neighbors = map.getAdjacentNodes(node);

        REQUIRE(neighbors.size() == 6);
    }

    SECTION("Cvorovi na ivicama nece imati svih 6 suseda")
    {
        Map map = Map(100, 100, 200, 200, 400, 400, 12);
        Node node1, node2, node3;
        std::vector<Node> neighbors1;
        std::vector<Node> neighbors2;
        std::vector<Node> neighbors3;
        bool condition;

        node1 = map.getNode(0, 0);
        node2 = map.getNode(map.height()-1, map.width()-1);
        node3 = map.getNode(10, map.width()-1);
        neighbors1 = map.getAdjacentNodes(node1);
        neighbors2 = map.getAdjacentNodes(node2);
        neighbors3 = map.getAdjacentNodes(node3);
        condition = neighbors1.size() < 6 &&
                neighbors2.size() < 6 &&
                neighbors3.size() < 6;

        REQUIRE(condition);
    }
    
    SECTION("Metod getIndices() za date koordinate cvora iz mape\
    vraca njegove indekse")
    {
        int i = 6, j = 10;
        Map map = Map(100, 100, 200, 200, 400, 400, 12);
        std::pair<int, int> indices;
        Node node;
        bool condition;

        node = map.getNode(i, j);
        indices = map.getIndices(node.getX(), node.getY());
        condition = indices.first == i && indices.second == j;

        REQUIRE(condition);
    }

    SECTION("Metod getNodePolygon() vraca temena sestougla jednog polja;\
    za susedna polja ce se poklapati odgovarajuca temena")
    {
        Map map = Map(100, 100, 200, 200, 400, 400, 12);
        Node node1, node2;
        std::vector<Point> poly1, poly2;
        bool condition;

        node1 = map.getNode(5, 6);
        node2 = map.getNode(6, 6);
        poly1 = map.getNodePolygon(node1.getX(), node1.getY());
        poly2 = map.getNodePolygon(node2.getX(), node2.getY());
        condition = poly1[4].first == poly2[2].first &&
                poly1[4].second == poly2[2].second &&
                poly1[5].first == poly2[1].first &&
                poly1[5].second == poly2[1].second;

        REQUIRE(condition);
    }

}