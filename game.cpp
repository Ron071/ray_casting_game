#include "game.h"
#include <iostream>
#include <SFML/Audio.hpp>


Game::Game(){  
}
void Game::game(){
    sf::RenderWindow windowOne(VideoMode(SW, SW), "MAZE");
    sf::RenderWindow windowTwo(VideoMode(BW, BW), "GAME");
    windowOne.setFramerateLimit(30);
    // int avr = 0;
    // int count = 0;
    windowOne.setSize(Vector2u(SW,SW));
    windowTwo.setSize(Vector2u(BW,BW));
    // sf::Clock clock; 
    // sf::Time deltaTime;
    while(windowOne.isOpen() && windowTwo.isOpen()){
        Event event;
        while(windowOne.pollEvent(event)){
            if(event.type == Event::Closed){
                windowOne.close();
                windowTwo.close();
                exit(0);
            }    
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
            player.move(maze);
        }
        if(Keyboard::isKeyPressed(Keyboard::A)){
            player.turnL();
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            player.turnR();
        }
        /*if(Keyboard::isKeyPressed(Keyboard::U)){
            update();
        }*/
        windowOne.clear();
        windowTwo.clear();
        maze.draw(windowOne);
        player.draw(&windowOne, &windowTwo, &maze);
        windowTwo.display();  
        windowOne.display();
        // avr += (int)(1.0f / deltaTime.asSeconds());
        // count++;
        // if(count%500 == 0){
        //     std::cout <<  "FPS " << avr/count << std::endl;
        //     count = 0;
        //     avr = 0;
        // }
        // deltaTime = clock.restart();
    }
}
void Game::update(){
    player.reset();
    maze.updateMaze();
}




////   g++ -g game.cpp main.cpp maze.cpp player.cpp ray.cpp  -lsfml-graphics -lsfml-window -lsfml-system -pthread -o game
