//
// Created by adamm on 25-03-06.
//

#ifndef ENTITY_H
#define ENTITY_H
#include<SFML/Graphics.hpp>

class Entity {
public:
    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Entity() = default;
};

#endif //ENTITY_H
