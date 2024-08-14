#include "ray.h"
#include "player.h"
#include "maze.h"
#include <iostream>
#include <cmath>
using namespace std;

Ray::Ray():ray(Lines, 2){} 
void Ray::setPoints(Vector2f one, Vector2f two){
    ray[0] = one;
    ray[1] = two;
}
void Ray::draw(RenderWindow& w) const{
    w.draw(ray);
}
float Ray::len()const {
    return len_of_ray;
}
Vector2f Ray::getcurr() const{
    return curr;
}
sf::Vector2f Ray::finalPoint(float angle, const Maze& m,  Vector2f current){
    float len = 0;
    sf::Vector2f direction(std::cos(angle), std::sin(angle));
    Vector2f res = current;
    int count = 0;
    float tempx;
    float tempy;
    while(count < 10){
        count++;
        if(angle <= (PI/2) || angle >= (1.5*PI)){
            tempx = ((int)current.x/CUBE+1)*(CUBE) -current.x;
        } 
        else{
        tempx = current.x - (int)current.x/CUBE*CUBE;  
        } 
        if(angle < PI ){
            tempy = ((int)current.y/CUBE +1)*(CUBE) - current.y;
        } 
        else {
            tempy = current.y - ((int)current.y/CUBE)*CUBE;
        }
        float z1 = abs(tempy/sin(angle));
        float z2 = abs(tempx/cos(angle));
        float t = fmin(z1, z2)+0.001;
        len += fmin(z1, z2);
        current+=direction*t;
        if(len >= RAY_LEN){
            len = RAY_LEN;
            break;
        }
        if(!m.getCell((int)current.y/CUBE, (int)current.x/CUBE)){
            break;
        }
    }
    res += direction*len;
    len_of_ray = len;
    curr = res;
    return res;
}

