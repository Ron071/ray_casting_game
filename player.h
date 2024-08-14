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
    CircleShape p;
    std::vector<Ray> rays;
    sf::Texture wall_texture;
    sf::Sprite wall_sprite;
    sf::Texture sky_texture;
    sf::Sprite sky_sprite;
    sf::Texture floor_texture;
    sf::Sprite floor_sprite;
    public:
        Player();
        void draw(RenderWindow& w,RenderWindow& w2, const Maze& m);
        bool checkCollision(const Maze& m) const;
        void move();
        void turnR();
        void turnL();
        void reset();
};


#endif //PLAYER_H