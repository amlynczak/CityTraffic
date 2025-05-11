#ifndef BUS_H
#define BUS_H

#include"Vehicle.h";
#include<vector>
#include<utility>
#include<queue>
#include<map>
#include<set>

class Bus : public Vehicle {
public:
	Bus(int id);
	Bus(int id, float x, float y, float velocity, Direction dir);
	void setRandomRoute(int stops, const Map& map);
	void setRoute(std::vector<std::pair<float, float>> route);
	std::vector<std::pair<float, float>> getRoute() const;
	void update(float delta, Map& map) override;

	std::queue<std::pair<int, int>> calculatePath(std::pair<int, int> startPoint, std::pair<int, int> endPoint, const Map& map);
private:
	std::vector<std::pair<float, float>> _route;
	std::queue<std::pair<int, int>> _path;
	int _currentStop;
	float _stopTime;
	bool _atStop;
};

#endif //BUS_H
