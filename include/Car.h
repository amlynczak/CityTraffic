#ifndef CAR_H
#define CAR_H

#include"Vehicle.h";

class Car : public Vehicle {
	Car(int id, float x, float y, float velocity) : Vehicle(id, x, y, velocity) {}
	void update(float delta) override;
};

#endif //CAR_H
