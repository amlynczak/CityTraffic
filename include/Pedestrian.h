#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include"Entity.h"

class Pedestrian : public Entity {
	Pedestrian(int id, float x, float y) : Entity(id, x, y) {}
	void update(float delta) override;
};

#endif //PEDESTRIAN_H
