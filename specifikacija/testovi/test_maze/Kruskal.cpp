#include "Kruskal.h"
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>


Kruskal::Kruskal(int n, int m)
    :Maze(n,m)
{
    // initiate skeleton
    for(int i = 0; i<_n; i++){
        for(int j = 0; j<_m; j++){
            if(i % 2 == 0){
                if(j % 2 == 0){
                    _maze[i][j] = 1;
                    celije.insert(std::pair(std::pair(i,j),std::pair(i,j)));
                } else {
                    _maze[i][j] = 2;
                    zidovi.push_back(std::pair(i,j));
                }

            } else if(j % 2 == 1){
                _maze[i][j] = 0;
            } else {
                _maze[i][j] = 2;
                zidovi.push_back(std::pair(i,j));

            }
        }
    }
}


ParParova find(MapaParova *map, Par p,Par q){
    if( p != map->find(p)->second or q != map->find(q)->second){
        auto tmp = find(map, map->find(p)->second, map->find(q)->second);
        map->find(p)->second = tmp.first;
        map->find(q)->second = tmp.second;
    }

    return ParParova(map->find(p)->second, map->find(q)->second);
}

void Kruskal::generate()
{
    auto rng = std::default_random_engine {};
    rng.seed(std::time(0));
    std::shuffle(std::begin(zidovi), std::end(zidovi), rng);

     // celije => 1  ; potencijani zid => 2 ;  zid => 0

    int i = 0;
    for(const auto& w : zidovi){
        i++;
        ParParova par;
        if(w.first % 2 == 1){
            int wi1 = w.first==0 ? 32 : w.first-1;
            int wi2 = w.first==32 ? 0 : w.first+1;
            par = find(&celije,Par(wi1,w.second),Par(wi2,w.second));
        }
        else{
            int wj1 = w.second==0 ? 22 : w.second-1;
            int wj2 = w.second==22 ? 0 : w.second+1;
            par = find(&celije,Par(w.first,wj1),Par(w.first,wj2));
        }

        _maze[w.first][w.second] = par.first != par.second ? 1 : 0;
        if(par.first != par.second){
            celije.find(par.first)->second = par.second;
        }
    }
}
