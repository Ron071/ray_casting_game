#include "player.h"




Player::Player():player(CircleShape(1)){
    player.setOrigin(0.5,0.5);
    player.setPosition(20,20);
    for(int i = 0; i < RAYS; i++)rays.push_back(Ray());
}

float findDirection(int i, float direction){
    return atan((float)2*i/RAYS)+direction;///may be tailor 
}


void Player::draw(RenderWindow& windowOne,RenderWindow& windowTwo, const Maze& m){
        windowOne.draw(player);
        Vector2f current = player.getPosition();
        float direction = player.getRotation()-45;
        for(int i = 0; i < RAYS; i++){
            //direction = findDirection(i, direction);
            rays[i].setPoints(current, rays[i].finalPoint(direction+(float)90/RAYS*i, m, current));
            //rays[i].draw(windowOne);
        }
}
    bool Player::checkCollision(const Maze& maze) const {
        Vector2f willBe = player.getPosition() + Vector2f(cos(player.getRotation()), sin(player.getRotation()))*(float)0.01;
        return maze.getCell((int)willBe.x/CUBE,(int)willBe.y/CUBE);
    }
    void Player::move(const Maze& maze){
        if(!checkCollision(maze))player.move(Vector2f(sin(player.getRotation()), cos(player.getRotation()))*(float)3);
    }
    void Player::turnR(){
        player.rotate(1);
    }
    void Player::turnL(){
        player.rotate(-1);
    }
    void Player::reset(){}
