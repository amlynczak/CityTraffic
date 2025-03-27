#include "Simulation.h"
#include "Car.h"
#include "Pedestrian.h"
#include "Bus.h"
#include <iostream>
#include <thread>
#include <chrono>

Simulation::Simulation() : _running(false) {}

void Simulation::init() {
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

	_map.loadFromFile("res/map.txt");

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