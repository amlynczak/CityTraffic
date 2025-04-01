#include "Simulation.h"
#include "Car.h"
#include "Pedestrian.h"
#include "Bus.h"
#include <iostream>
#include <thread>
#include <chrono>

Simulation::Simulation() : _running(false) {}

void Simulation::init() {
	if (!_map.loadFromFile("../../../../resources/map.csv")) {
		std::cerr << "Error: cannot load map from file" << std::endl;
		return;
	}
	_map.printMap();
	std::vector<std::pair<int, int>> startPositions = _map.getStartPositions();

	int random = rand() % startPositions.size();
	Direction dir;
	if (startPositions[random].first == 0) {
		dir = Direction::RIGHT;
	}
	else if(startPositions[random].first == _map.getWidth() - 1){
		dir = Direction::LEFT;
	}
	else if (startPositions[random].second == 0) {
		dir = Direction::DOWN;
	}
	else {
		dir = Direction::UP;
	}

	auto car1 = std::make_shared<Car>(1, startPositions[random].first, startPositions[random].second, 1, dir);
	car1->setSpeed(50.0f);
	_entityManager.addEntity(car1);

	random = rand() % startPositions.size();
	if (startPositions[random].first == 0) {
		dir = Direction::RIGHT;
	}
	else if (startPositions[random].first == _map.getWidth() - 1) {
		dir = Direction::LEFT;
	}
	else if (startPositions[random].second == 0) {
		dir = Direction::DOWN;
	}
	else {
		dir = Direction::UP;
	}
	auto car2 = std::make_shared<Car>(2, startPositions[random].first, startPositions[random].second, 1, dir);
	car2->setSpeed(50.0f);
	_entityManager.addEntity(car2);

	_running = true;
}

void Simulation::run() {
	const float dt = 1.0f / 60.0f;
	while (_running) {
		update(dt);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Simulation::update(float dt) {
	_entityManager.updateAll(dt, _map);
	_lights.update(dt);
}

bool Simulation::isRunning() const {
	return _running;
}

void Simulation::stop() {
	_running = false;
}