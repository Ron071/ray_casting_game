#ifndef PLAYER_H
#define PLAYER_H

#include "ray.h"
#include "maze.h"
#include "SFML/Graphics.hpp"
using namespace sf;
#define SPEED 0.3
#define RAYS 600
#define ANGLE 90

class Player{
    CircleShape player;
    std::vector<Ray> rays;
    public:
        Player();
        void draw(RenderWindow& windowOne,RenderWindow& windowTwo, const Maze& maze);
        bool checkCollision(const Maze& maze) const;
        void move(const Maze& maze);
        void turnR();
        void turnL();
        void reset();
};


#endif //PLAYER_H