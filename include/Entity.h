#ifndef ENTITY_H
#define ENTITY_H

#include"Map.h"

enum class Direction { UP, DOWN, RIGHT, LEFT};

class Entity {
public:
	Entity(int id, float x, float y, Direction dir) : _id(id), _x(x), _y(y), _dir(dir) {};
    virtual ~Entity() = default;

	virtual void update(float delta, const Map& map) = 0;

	int getId() const { return _id; }
	float getX() const { return _x; }
	float getY() const { return _y; }
	Direction getDir() const { return _dir; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setDir(Direction dir) { _dir = dir; }

protected:
    int _id;
	float _x;
	float _y;
	Direction _dir;
};

#endif
