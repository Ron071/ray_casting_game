#ifndef RAY_H
#define RAY_H
#include "maze.h"
#include "SFML/Graphics.hpp"
#define RAY_LEN 120
using namespace sf;


class Ray{
    VertexArray ray;
    float len_of_ray;
    Vector2f curr;
    public:
        Ray();
        Vector2f getcurr() const;
        void setPoints(Vector2f one, Vector2f two);
        void draw(RenderWindow& w) const;
        float len() const;
        sf::Vector2f finalPoint(float angle, const Maze& m,  Vector2f current);
};

#endif //RAY_H