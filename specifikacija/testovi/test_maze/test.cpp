#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "Maze.h"
#include "Kruskal.h"
#include "RandomMaze.h"
#include <vector>
#include <algorithm>



TEST_CASE("Maze", "[class]")
{
    SECTION("Provera getera za n,m")
    {
        int n = 9;
        int m = 11;
        Kruskal map(n,m);

        int _n = map.getN();
        int _m = map.getM();

        REQUIRE(n == _n);
        REQUIRE(m == _m);


    }
}

TEST_CASE("Kruskal", "[class]")
{
    SECTION("Mapa velicine n = 0, m = 0 ne moze imati prepreke")
    {
        Kruskal map(0,0);

        map.generate();
        int obst_count = map.getObstacles().size();

        REQUIRE(obst_count == 0);
        
    }

    SECTION("Mapa velicine n = 1 ne moze imati prepreke")
    {
        Kruskal map(1,10);

        map.generate();
        int obst_count = map.getObstacles().size();

        REQUIRE(obst_count == 0);
        
    }

    SECTION("Mapa velicine m = 1 ne moze imati prepreke")
    {
        Kruskal map(10,1);

        map.generate();
        int obst_count = map.getObstacles().size();

        REQUIRE(obst_count == 0);
        
    }

    SECTION("Mapa mora da ima najmanje n/2 * m/2 prepreka")
    {
        int n = 10;
        int m = 20;
        Kruskal map(n,m);
        
        int obst_count = map.getObstacles().size();
        int minimum_obst = n/2 * m/2;

        REQUIRE(obst_count >= minimum_obst);

    }

    SECTION("Prepreke ne smeju da izlaze van granica")
    {
        int m = 10;
        Kruskal map(m,m);

        VektorParova obst = map.getObstacles();
        int obst_count = obst.size();
        int good_obst = 0;
        for(Par& x : obst){
            if(x.first>= 0 && x.first < m && x.second>= 0 && x.second < m)
                good_obst++;
        }

        REQUIRE(obst_count == good_obst);

    }

    SECTION("Prepreke moraju postojati ako su pozicije neparne")
    {
        int n = 10;
        int m = 10;
        Kruskal map(n,m);    

        int good_obst = 0;
        int expected_obst = n/2 * m/2;
        VektorParova obst = map.getObstacles();
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                if(i % 2 == 1 && j % 2 == 1)
                {
                    std::pair elem(i,j);
                    if(std::find(obst.begin(),obst.end(),elem) != obst.end())
                        good_obst++;
                }
                    
            }
        }

        REQUIRE(good_obst == expected_obst);
    }


}

TEST_CASE("RandomMaze", "[class]")
{
    SECTION("Mapa velicine n = 0, m = 0 ne moze imati prepreke")
    {
        RandomMaze map(0,0);

        map.generate();
        int obst_count = map.getObstacles().size();

        REQUIRE(obst_count == 0);
    }

    SECTION("Za dovoljno veliku mapu mora postojati barem jedna prepreka")
    {

        RandomMaze map (100,100);

        map.generate();
        int obst_count = map.getObstacles().size();

        REQUIRE(obst_count > 0);
    }

}