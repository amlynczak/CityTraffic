#include"Entity.h"

Entity::Entity(int id) : _id(id), _x(0), _y(0), _dir(Direction::NONE) {};

Entity::Entity(int id, float x, float y, Direction dir) : _id(id), _x(x), _y(y), _dir(dir) {};


int Entity::getId() const {
    return _id;
}

float Entity::getX() const {
    return _x;
}

float Entity::getY() const {
    return _y;
}

Direction Entity::getDir() const {
    return _dir;
}

void Entity::setX(float x){
    _x = x;
}

void Entity::setY(float y){
    _y = y;
}

void Entity::setDir(Direction dir){
    _dir = dir;
}