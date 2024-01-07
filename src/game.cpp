#include "../include/game.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Texture.hpp>

static float PlayerSpeed = 100.f;
static sf::Time TimePerFrame = sf::seconds(1.f/60.f); //60 FPS - 60 frames/second,  ~0.016666667 seconds

Game::Game() : mWindow(sf::VideoMode(640,480), "SFML Application"),mTexture(), mPlayer(){
    //texture: the image itself
    //sprite: where and how to put the image

    if (!mTexture.loadFromFile("resources/textures/scope_cop_smol.png")) {
        //handle error
    }

    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f,100.f); //where player starts
}

void Game::run(){

    //fixed time steps!
    //it restricts the frame rate to a certain value, but it prevents lagging through object lets say for example iterations
    //could be slower or faster then you would have different frame times

    //refer to sfml book fixed time steps chapter!!!!!

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; // intialize to 0

    while (mWindow.isOpen()) {
 
        processEvents();
        timeSinceLastUpdate += clock.restart(); // time elapsed while processEvents() did its thing

        while (timeSinceLastUpdate > TimePerFrame) { // ~0.0166666667
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();

    }
    
}

void Game::processEvents(){
    sf::Event event;

    while (mWindow.pollEvent(event)) {

        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code,true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code,false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        
        }
    }
}

void Game::update(sf::Time deltaTime){
    sf::Vector2f movement(0.f,0.f);

    if (mIsMovingUp) {
        movement.y -= PlayerSpeed;
    }
    if (mIsMovingDown) {
        movement.y += PlayerSpeed;
    }
    if (mIsMovingLeft) {
        movement.x -= PlayerSpeed;
    }
    if (mIsMovingRight) {
        movement.x += PlayerSpeed;
    }

    mPlayer.move(movement * deltaTime.asSeconds()); // v = s*t
}

void Game::render(){
    

    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key,bool isPressed){
    if (key == sf::Keyboard::W) {
        mIsMovingUp = isPressed;
    }
    if (key == sf::Keyboard::S) {
        mIsMovingDown = isPressed;
    }
    if (key == sf::Keyboard::A) {
        mIsMovingLeft = isPressed;
    }
    if (key == sf::Keyboard::D) {
        mIsMovingRight = isPressed;
    }
}
