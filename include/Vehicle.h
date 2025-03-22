#ifndef VEHICLE_H
#define VEHICLE_H

#include"Entity.h";

class Vehicle : public Entity{
public:
	Vehicle(int id, float x, float y, float velocity) : Entity(id, x, y), _velocity(velocity) {}
	virtual void update(float delta) = 0;
	float getVelocity() const { return _velocity; }
	void setVelocity(float velocity) { this->_velocity = velocity; }
protected:
	float _velocity;
};

#endif //VEHICLE_H
