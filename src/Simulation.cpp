#include "Simulation.h"
#include "Car.h"
#include "Pedestrian.h"
#include "Bus.h"
#include <iostream>
#include <thread>
#include <chrono>

Simulation::Simulation() : _running(false) {}

void Simulation::init() {
	if (!_map.loadFromFile("../../../../resources/city_100x40.csv")) {
		std::cerr << "Error: cannot load map from file" << std::endl;
		return;
	}
	_map.printMap();

	_entityManager.addEntity(std::make_shared<Car>(1, 0, 0, 1, Direction::HOR));
	_entityManager.addEntity(std::make_shared<Car>(2, 0, 0, 1, Direction::VERT));
	_entityManager.addEntity(std::make_shared<Pedestrian>(3, 0, 0, Direction::HOR));
	_entityManager.addEntity(std::make_shared<Bus>(4, 0, 0, 1, Direction::VERT));
	
	std::vector<std::pair<float, float>> route = {
		{0, 0},
		{0, 10},
		{10, 10},
		{10, 0},
		{0, 0}
	};

	_running = true;
}

void Simulation::update(float dt) {
	_entityManager.updateAll(dt);
	_lights.update(dt);
}

bool Simulation::isRunning() const {
	return _running;
}

void Simulation::stop() {
	_running = false;
}