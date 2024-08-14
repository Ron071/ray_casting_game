#include "game.h"
#include <iostream>
#include <SFML/Audio.hpp>


Game::Game(){  
}
void Game::game(){
    sf::RenderWindow w(VideoMode(SW, SW), "MAZE");
    sf::RenderWindow w2(VideoMode(BW, BW), "GAME");
    w2.setFramerateLimit(120);
    sf::Clock clock;
    sf::Time deltaTime;
    sf::Music music;
    //music.openFromFile("chipi.mp3");
    //music.play();
    sf::Font font;
    font.loadFromFile("text.ttf");
    int i = 0;
    sf::Text text;
    text.setFont(font);
    while(w2.isOpen()){
        Event event;
        while(w2.pollEvent(event)){
            if(event.type == Event::Closed){
                w.close();
                w2.close();
            }    
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
            if(!p.checkCollision(m))p.move();
        }
        if(Keyboard::isKeyPressed(Keyboard::A)){
            p.turnL();
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            p.turnR();
        }
        if(Keyboard::isKeyPressed(Keyboard::U)){
            update();
        }
        deltaTime = clock.restart();
        w.clear();
        w2.clear();
        m.draw(w);
        p.draw(w, w2, m);
        w2.draw(text);
        if(i > 100){
            float fps = 1.0f / deltaTime.asSeconds();
            text.setString("FPS: " + std::to_string((int)round(fps / 10) * 10));
            text.setCharacterSize(35);
            text.setFillColor(sf::Color::Black);
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            text.setPosition(Vector2f(10,10));
            i=0;
        }
        i++;
        w2.display();  
    }
}
void Game::update(){
    p.reset();
    m.updateMaze();
}