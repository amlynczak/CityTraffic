#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include"Entity.h"

class Pedestrian : public Entity {
public:
	Pedestrian(int id, float x, float y, Direction dir);
	void update(float delta) override;
};

#endif //PEDESTRIAN_H
