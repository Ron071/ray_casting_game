#include "player.h"
#include <iostream>
#include <unistd.h>
#define RADIANS(x) (((float)x/180*PI))

#define SW 285
#define BW 600

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
struct Data { //// 1000 rays 150% cpu, 420 fps(on cold 900). 750 145 420. 500 110 470. 300 130 550  
    int startIndex;
    int endIndex;
    const Maze* maze;
    Player* player;

    Data(int start, int end, const Maze* maze, Player* player)
        : startIndex(start), endIndex(end), maze(maze), player(player) {}
};
void* processRays(void* args) {
    Data* data = static_cast<Data*>(args);
    for (int i = data->startIndex; i < data->endIndex; ++i) {
        float direction = atan((float)2 * (i - RAYS / 2) / RAYS) + data->player->rotation();
        if (direction > 2 * PI) direction -= 2 * PI;
        else if (direction < 0) direction += 2 * PI;
        data->player->ray(i)->setPoints(data->player->position(),
            data->player->ray(i)->finalPoint(direction, data->maze, data->player->position())
        );
    }
    return nullptr;
}
// void Player::draw(RenderWindow* windowOne, RenderWindow* windowTwo, const Maze* maze) {   ///100k 40fps 
//     windowOne->draw(player);
//     const int THREAD_COUNT = 6 < RAYS ? 6:RAYS; // to class 
//     pthread_t threads[THREAD_COUNT];
//     std::vector<Data*> threadData;
//     int raysPerThread = RAYS / THREAD_COUNT;
//     for (int t = 0; t < THREAD_COUNT; ++t) {
//         int startIndex = t * raysPerThread;
//         threadData.push_back(new Data(startIndex, startIndex + raysPerThread, maze, this));
//         pthread_create(&threads[t], nullptr, processRays, threadData[t]);
//     }
//     for (int t = 0; t < THREAD_COUNT; ++t) {
//         pthread_join(threads[t], nullptr);
//         delete threadData[t];  // in destructor 
//     }
//     for (int t = 0; t < RAYS; ++t){
//         rays[t].draw(windowOne);
//     }
// }

void Player::draw(RenderWindow* windowOne,RenderWindow* windowTwo, const Maze* maze){/// 100k 22fps 
        windowOne->draw(player);
        Vector2f current = player.getPosition();
        float rotation = RADIANS(player.getRotation());
        for(int i = 0; i < RAYS; i++){
            float direction = atan((float)2*(i-RAYS/2)/RAYS);// make it depend on the ANGLE 
            float cosAngle = cos(direction);
            direction += rotation;
            if(direction > 2*PI)direction -= 2*PI;
            else if (direction < 0)direction += 2*PI;
            rays[i].setPoints(current, rays[i].finalPoint(direction, maze, current));
            rays[i].draw(windowOne);
            float height =(float)BW*CUBE/rays[i].len()/cosAngle;
            RectangleShape shape(Vector2f((float)BW/RAYS, height));
            shape.setFillColor(Color(0,256*(1-(float)rays[i].len()/RAY_LEN), 0));
            shape.setPosition(i, 0.5*(BW-height));
            windowTwo->draw(shape);
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
