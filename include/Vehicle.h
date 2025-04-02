#ifndef VEHICLE_H
#define VEHICLE_H

#include"Entity.h";

class Vehicle : public Entity{
public:
	Vehicle(int id) : Entity(id) {}
	Vehicle(int id, float x, float y, Direction dir, float speed) : Entity(id, x, y, dir), _speed(speed) {}
	virtual ~Vehicle() = default;

	virtual void update(float delta, const Map& map) = 0;

	void placeOnMap(const Map& map) override;
	float getSpeed() const;
	void setSpeed(float speed);
protected:
	float _speed;
};

#endif