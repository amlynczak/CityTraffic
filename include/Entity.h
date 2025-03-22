//
// Created by adamm on 25-03-06.
//

#ifndef ENTITY_H
#define ENTITY_H
#include<SFML/Graphics.hpp>

class Entity {
public:
    virtual void update(float delta) = 0;
    virtual ~Entity() = default;

	int getId() const { return _id; }
	float getX() const { return _x; }
	float getY() const { return _y; }

protected:
    int _id;
	float _x;
	float _y;
};

#endif //ENTITY_H
