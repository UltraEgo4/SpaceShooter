#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Vector2.hpp>


class Entity{
public:

    Entity();

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity(sf::Vector2f velocity) const;

private:
    sf::Vector2f mVelocity;


};


#endif  //ENTITY_H