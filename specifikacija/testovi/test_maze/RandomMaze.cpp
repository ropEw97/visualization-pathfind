#include "RandomMaze.h"
#include <stdlib.h>     
#include <time.h>
#include <vector>


RandomMaze::RandomMaze(int n, int m)
    :Maze(n,m)
{
    for(int i = 0; i<_n; i++){
        for(int j = 0; j<_m; j++){
            _maze[i][j] = 1;
        }
    }
}

void RandomMaze::generate()
{
    srand(time(NULL));
    for(int i = 0; i<_n; i++){
        for(int j = 0; j<_m; j++){
            double rng = rand() / RAND_MAX;
            if(rng < 0.33){
                _maze[i][j] = 0;
            }
        }
    }
}


