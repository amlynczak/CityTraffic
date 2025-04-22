#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include"Entity.h"

class Pedestrian : public Entity {
public:
	Pedestrian(int id);
	Pedestrian(int id, float x, float y, Direction dir);
	void placeOnMap(const Map& map) override;
	void update(float delta, Map& map) override;
};

#endif //PEDESTRIAN_H
