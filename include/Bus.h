#ifndef BUS_H
#define BUS_H

#include"Vehicle.h";
#include<vector>
#include<utility>

class Bus : public Vehicle {
public:
	Bus(int id, float x, float y, float velocity) : Vehicle(id, x, y, velocity) {}
	void update(float delta) override;

private:
	std::vector<std::pair<float, float>> _route;
	size_t _currentStop;
	float _stopTime;
	bool atStop;
};

#endif //BUS_H
