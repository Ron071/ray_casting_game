#include "player.h"
#include <iostream>
#include <unistd.h>
#define RADIANS(x) (((float)x/180*PI))

/////getRotation return in degreee but all trigonomic function expext to get in radians 


pthread_mutex_t lock;

Player::Player():player(CircleShape(1,5)){
    player.setPosition(20,20);
    player.setOrigin(1,1);
    for(int i = 0; i < RAYS; i++)rays.push_back(Ray());
    pthread_mutex_init(&lock, nullptr);
}
float Player::rotation(){
    return RADIANS(player.getRotation());
}
Vector2f Player::position(){
    return player.getPosition();
}
Ray* Player::ray(int i){
    return &rays[i];
}
Player::~Player(){
    pthread_mutex_destroy(&lock);
}


void* f(void* args){
    Data* data = static_cast<Data*>(args); 
    int j = data->i*RAYS/2;
    float rotation = data->player->rotation();
    Vector2f position = data->player->position();
    for(int i = 0; i < RAYS/2; i++){
        float direction = atan((float)2*(i+j-RAYS/2)/RAYS)+rotation;
        if(direction > 2*PI)direction -= 2*PI;
        else if (direction < 0)direction += 2*PI;
        data->player->ray(i+j)->setPoints(position, data->player->ray(i+j)->finalPoint(direction, data->maze, position));
        pthread_mutex_lock(&lock);
        data->player->ray(i+j)->draw(data->windowOne);
        pthread_mutex_unlock(&lock);
    }
    return nullptr;
}
/*void Player::draw(RenderWindow* windowOne,RenderWindow* windowTwo, const Maze* maze){ // for many threads 
        windowOne->draw(player);
        pthread_t threads[2];
        for(int i = 0; i < 2; i++){// after will combine it to seperate function for pthreads 
            Data* treadData = new Data(i, windowOne, windowTwo, maze, this);
            pthread_create(&threads[i], NULL, &f, treadData);
        }
        for(int i = 0; i < RAYS; i++){
            pthread_join(threads[i], NULL);
        }
}*/

void Player::draw(RenderWindow* windowOne,RenderWindow* windowTwo, const Maze* maze){
        windowOne->draw(player);
        Vector2f current = player.getPosition();
        float rotation = RADIANS(player.getRotation());
        for(int i = 0; i < RAYS; i++){
            float direction = atan((float)2*(i-RAYS/2)/RAYS)+rotation;// make it depend on the ANGLE 
            if(direction > 2*PI)direction -= 2*PI;
            else if (direction < 0)direction += 2*PI;
            rays[i].setPoints(current, rays[i].finalPoint(direction, maze, current));
            rays[i].draw(windowOne);
            ///add for second(main) screen
        }
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
