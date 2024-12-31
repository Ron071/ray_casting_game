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
void Ray::draw(RenderWindow& windowOne) const{
    windowOne.draw(ray);
}
Vector2f Ray::finalPoint(float angle, const Maze& maze,  Vector2f current){  // angle in radians
    float len = 0;
    Vector2f direction(std::cos(angle), std::sin(angle));
    Vector2f res = current;
    float tempx;
    float tempy;
    while(1){
        if(angle <= (PI/2) || angle >= (1.5*PI)){
            tempx = ((int)current.x/CUBE+1)*(CUBE)-current.x;
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
        float z1 = abs(tempy/(sin(angle) != 0 ? sin(angle) : 1e-6));
        float z2 = abs(tempx/(cos(angle) != 0 ? cos(angle) : 1e-6));
        float t = fmin(z1, z2)+0.01;
        len += t-0.01;
        current+=direction*t;
        if(len >= RAY_LEN){
            len = RAY_LEN;
            break;
        }
        if(!maze.getCell((int)current.y/CUBE, (int)current.x/CUBE)){
            break;
        }
    }
    res += direction*len;
    return res;
}

