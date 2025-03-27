#ifndef BUS_H
#define BUS_H

#include"Vehicle.h";
#include<vector>
#include<utility>

class Bus : public Vehicle {
public:
	Bus(int id, float x, float y, float velocity, Direction dir);
	void setRoute(std::vector<std::pair<float, float>> route);
	void update(float delta) override;

private:
	std::vector<std::pair<float, float>> _route;
	int _currentStop;
	float _stopTime;
	bool _atStop;
};

#endif //BUS_H
