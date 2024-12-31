#ifndef RAY_H
#define RAY_H
#include "maze.h"
#include "SFML/Graphics.hpp"
#define RAY_LEN 50
using namespace sf;


class Ray{
    VertexArray ray;
    public:
        Ray();
        void setPoints(Vector2f one, Vector2f two);
        void draw(RenderWindow* windowOne) const;
        sf::Vector2f finalPoint(float angle, const Maze* maze,  Vector2f current);
};

#endif //RAY_H