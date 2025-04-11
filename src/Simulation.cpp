#include "Simulation.h"
#include "Simulation.h"
#include "Simulation.h"
#include "Car.h"
#include "Pedestrian.h"
#include "Bus.h"
#include <iostream>
#include <thread>
#include <chrono>

Simulation::Simulation() : _running(false) 
{
	if (!_map.loadFromFile("../../../../resources/map.csv")) {
		std::cerr << "Error: cannot load map from file" << std::endl;
		return;
	}
	_map.printMap();

	for (int i = 0; i < 2; ++i) {
		auto car = std::make_shared<Car>(i + 1);
		car->placeOnMap(_map);
		_entityManager.addEntity(car);
	}

	for (int i = 0; i < 1; ++i) {
		auto pedestrian = std::make_shared<Pedestrian>(2 + i + 1);
		pedestrian->placeOnMap(_map);
		_entityManager.addEntity(pedestrian);
	}

	for (int i = 0; i < 1; ++i) {
		auto bus = std::make_shared<Bus>(2 + 1 + i + 1);
		bus->placeOnMap(_map);
		bus->setRandomRoute(3, _map);
		_entityManager.addEntity(bus);
	}
}

Simulation::Simulation(int cars, int pedestrians, int buses, float cycleTime, int simulationSpeed) : _running(false)
{
	if (cars < 0 || pedestrians < 0 || buses < 0) {
		std::cerr << "Error: Number of cars, pedestrians, and buses must be non-negative." << std::endl;
		return;
	}
	if (cycleTime <= 0) {
		std::cerr << "Error: Cycle time must be positive." << std::endl;
		return;
	}
	if (simulationSpeed <= 0) {
		std::cerr << "Error: Simulation speed must be positive." << std::endl;
		return;
	}

	if (!_map.loadFromFile("../../../../resources/map.csv")) {
		std::cerr << "Error: cannot load map from file" << std::endl;
		return;
	}
	_map.printMap();

	for (int i = 0; i < cars; ++i) {
		auto car = std::make_shared<Car>(i + 1);
		car->placeOnMap(_map);
		_entityManager.addEntity(car);
	}

	for (int i = 0; i < pedestrians; ++i) {
		auto pedestrian = std::make_shared<Pedestrian>(cars + i + 1);
		pedestrian->placeOnMap(_map);
		_entityManager.addEntity(pedestrian);
	}

	for (int i = 0; i < buses; ++i) {
		auto bus = std::make_shared<Bus>(cars + pedestrians + i + 1);
		bus->placeOnMap(_map);
		_entityManager.addEntity(bus);
	}
}

void Simulation::run() {
	_running = true;
	const float dt = 1.0f / 60.0f;
	while (_running) {
		update(dt);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Simulation::update(float dt) {
	_entityManager.updateAll(dt, _map);
	//_lights.update(dt);
}

bool Simulation::isRunning() const {
	return _running;
}

Map& Simulation::getMap()
{
	return _map;
}

void Simulation::stop() {
	_running = false;
}