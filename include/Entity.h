#ifndef ENTITY_H
#define ENTITY_H

#include"Map.h"

enum class Direction { UP, DOWN, RIGHT, LEFT, NONE};

class Entity {
public:
	Entity(int id);
	Entity(int id, float x, float y, Direction dir);

    virtual ~Entity() = default;
	virtual void placeOnMap(const Map& map) = 0;
	virtual void update(float delta, Map& map) = 0;

	int getId()const;
	float getX()const;
	float getY()const;
	Direction getDir()const;

	void setX(float x);
	void setY(float y);
	void setDir(Direction dir);

protected:
    int _id;
	float _x;
	float _y;
	Direction _dir;
};

#endif
