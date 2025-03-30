#ifndef CAR_H
#define CAR_H

#include"Vehicle.h";

class Car : public Vehicle {
public:
	Car(int id, float x, float y, float speed, Direction dir);

	void update(float delta, const Map& map) override;
};

#endif //CAR_H
