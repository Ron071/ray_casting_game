#include "player.h"
#include <iostream>
#include <pthread.h>

/////getRotation return in degreee but all trigonomic function expext to get in radians 


Player::Player():player(CircleShape(2,3)){
    player.setPosition(20,20);
    player.setOrigin(2,2);
    for(int i = 0; i < RAYS; i++)rays.push_back(Ray());
}

float findDirection(int i, float direction){
    return atan((float)2*i/RAYS)/(2*PI)*360+direction;///may be tailor 
}


void Player::draw(RenderWindow& windowOne,RenderWindow& windowTwo, const Maze& maze){
        windowOne.draw(player);
        Vector2f current = player.getPosition();
        float direction = player.getRotation()/180*PI;
        //phtread_t threads[RAYS];
        for(int i = 0; i < 1; i++){
            //phread_create(&treads[i], NULL, findDirection, NULL);
            //direction = findDirection(i, direction);
            rays[i].setPoints(current, rays[i].finalPoint(direction, maze, current));//rays[i].finalPoint(direction+i*0.1, maze, current)
            rays[i].draw(windowOne);
        }
        for(int i = 0; i < RAYS; i++){
            //phread_join(treads[i], NULL);
        }
}
    bool Player::checkCollision(const Maze& maze) const {
        Vector2f willBe = player.getPosition() + Vector2f(cos(player.getRotation()/180*PI), sin(player.getRotation()/180*PI));
        return !(maze.getCell((int)willBe.y/CUBE,(int)willBe.x/CUBE));
    }
    void Player::move(const Maze& maze){
        if(!checkCollision(maze)){
            player.move(cos(player.getRotation()/180*PI), sin(player.getRotation()/180*PI));
        }
    }
    void Player::turnR(){
        player.rotate(10);
    }
    void Player::turnL(){
        player.rotate(-10);
    }
    void Player::reset(){}
