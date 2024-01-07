#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>


class Game{
public:
    Game();
    void run();


private:
    
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void handlePlayerInput(sf::Keyboard::Key key,bool isPressed);
    
    sf::RenderWindow mWindow;

    sf::Texture mTexture;
    sf::Sprite mPlayer;


    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

};


#endif  //GAME_H