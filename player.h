#ifndef PLAYER_H
#define PLAYER_H

#include "ray.h"
#include "maze.h"
#include "SFML/Graphics.hpp"
#include <pthread.h>
using namespace sf;
#define SPEED 0.3
#define RAYS 10
#define ANGLE 90




class Player{
    CircleShape player;
    std::vector<Ray> rays;
    public:
        Player();
        void draw(RenderWindow* windowOne,RenderWindow* windowTwo, const Maze* maze);
        float rotation();
        Vector2f position();
        Ray* ray(int i);
        bool checkCollision(const Maze& maze) const;
        void move(const Maze& maze);
        void turnR();
        void turnL();
        void reset();
        ~Player();
};



struct Data{
    int i;
    RenderWindow* windowOne;
    RenderWindow* windowTwo;
    const Maze* maze;
    Player* player;
    Data(int i, RenderWindow* windowOne, RenderWindow* windowTwo, const Maze* maze, Player* player):
    i(i), windowOne(windowOne), windowTwo(windowTwo), maze(maze), player(player){}
};

#endif //PLAYER_H