#include"Bus.h"
#include<iostream>

Bus::Bus(int id) : Vehicle(id), _currentStop(0), _stopTime(0), _atStop(false) {}

Bus::Bus(int id, float x, float y, float velocity, Direction dir) : Vehicle(id, x, y, dir, velocity), _currentStop(0), _stopTime(0), _atStop(false) {}

void Bus::setRandomRoute(int stops, const Map& map)
{
	_route.clear();
	_currentStop = 0;
	_stopTime = 0;
	_atStop = false;
	for (int i = 0; i < stops; ++i) {
		int x = rand() % map.getWidth();
		int y = rand() % map.getHeight();
		while (map.getTile(x, y) == 1) {
			x = rand() % map.getWidth();
			y = rand() % map.getHeight();
		}
		_route.push_back(std::make_pair(x, y));
		std::cout << "Bus" << _id << " stop " << i << ": (" << x << ", " << y << ")" << std::endl;
	}
}

void Bus::setRoute(std::vector<std::pair<float, float>> route) {
	_route = route;
}

void Bus::update(float delta, const Map& map) {
	if (_atStop) {
		_stopTime += delta;
		if (_stopTime >= 2.0f) { // Stop for 2 seconds
			_atStop = false;
			_stopTime = 0;
			_currentStop++;
			if (_currentStop >= _route.size()) {
				_currentStop = 0; // Loop back to the first stop
			}
		}
		return;
	}

	if (_route.empty()) return;

	auto [targetX, targetY] = _route[_currentStop];
	float dx = targetX - _x;
	float dy = targetY - _y;
	float distance = std::sqrt(dx * dx + dy * dy);

	if (distance < 0.1f) { // If the bus is close enough to the stop
		//_atStop = true;
		_stopTime = 0;
		if (_currentStop < _route.size() - 1) {
			_currentStop++;
		}
		else {
			_currentStop = 0; // Loop back to the first stop
		}
		return;
	}

	float moveDistance = 1; // _speed* delta;
	if (moveDistance > distance) {
		moveDistance = distance;
	}

	_x += moveDistance * (dx / distance);
	_y += moveDistance * (dy / distance);

	std::cout << "Bus" << _id << std::endl;
	std::cout << "Current position: (" << _x << ", " << _y << ")" << std::endl;
	std::cout << "Current stop: (" << targetX << ", " << targetY << ")" << std::endl;

	// Update direction based on movement
	if (std::abs(dx) > std::abs(dy)) {
		_dir = (dx > 0) ? Direction::RIGHT : Direction::LEFT;
	}
	else {
		_dir = (dy > 0) ? Direction::DOWN : Direction::UP;
	}

	//TODO: Check if the bus can travel to the next tile
}