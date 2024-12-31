#include "player.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#define RADIANS(x) (((float)x/180*PI))

/////getRotation return in degreee but all trigonomic function expext to get in radians 


Player::Player():player(CircleShape(1,5)){
    player.setPosition(20,20);
    player.setOrigin(1,1);
    for(int i = 0; i < RAYS; i++)rays.push_back(Ray());
}

float findDirection(int i){
    return atan((float)2*(i-RAYS/2)/RAYS);///may be tailor x-x^3/3+x^5/5...     atan((float)2*(i-RAYS/2)/RAYS)
}

void* f(void*){
    

}

void Player::draw(RenderWindow& windowOne,RenderWindow& windowTwo, const Maze& maze){
        windowOne.draw(player);
        Vector2f current = player.getPosition();
        float direction;
        float rotation = RADIANS(player.getRotation());
        //pthread_t  threads[RAYS];
        for(int i = 0; i < RAYS; i++){// after will combine it to seperate function for pthreads 
            //pthread_create(&threads[i], NULL, f, NULL);
            direction = findDirection(i)+rotation;///check with threads
            if(direction > 2*PI)direction -= 2*PI;
            else if (direction < 0)direction += 2*PI;
            rays[i].setPoints(current, rays[i].finalPoint(direction, maze, current));//rays[i].finalPoint(direction+i*0.1, maze, current)
            rays[i].draw(windowOne);
        }
        //for(int i = 0; i < RAYS; i++){
            //pthread_join(threads[i], NULL);
        //}
}
    bool Player::checkCollision(const Maze& maze) const {
        Vector2f willBe = player.getPosition() + Vector2f(cos(RADIANS(player.getRotation())), sin(RADIANS(player.getRotation())));
        return !(maze.getCell((int)willBe.y/CUBE,(int)willBe.x/CUBE));
    }
    void Player::move(const Maze& maze){
        if(!checkCollision(maze)){
            player.move(cos(RADIANS(player.getRotation())), sin(RADIANS(player.getRotation())));
        }
    }
    void Player::turnR(){
        player.rotate(5);
    }
    void Player::turnL(){
        player.rotate(-5);
    }
    void Player::reset(){}
