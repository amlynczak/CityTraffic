#ifndef VEHICLE_H
#define VEHICLE_H

#include"Entity.h";

class Vehicle : public Entity{
public:
	Vehicle(int id, float x, float y, Direction dir, float speed) : Entity(id, x, y, dir), _speed(speed) {}
	virtual ~Vehicle() = default;

	virtual void update(float delta) = 0;
	float getSpeed() const { return _speed; }
	void setSpeed(float speed) { _speed = speed; }
protected:
	float _speed;
};

#endif