#include "game.h"
#include <iostream>
#include <thread>

int main(){
    Game g;
    g.game();
    //std::cout << std::thread::hardware_concurrency();
    return 0;
}
