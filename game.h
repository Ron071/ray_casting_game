#ifndef GAME_H
#define GAME_H
#include "maze.h"
#include "player.h"
#define SW 285
#define BW 600

class Game{
    Player player;
    Maze maze;
    public:
        Game();
        void game();
        void update();
};



#endif //GAME_H