#include "Simulation.h"
#include "Car.h"
#include "Pedestrian.h"
#include "Bus.h"
#include <iostream>
#include <thread>
#include <chrono>

Simulation::Simulation() : _running(false), _numCars(5), _numPedestrians(2), _numBuses(1), _cycleTime(15.0f), _simulationSpeed(1)
{
	if (!_map.loadFromFile("../../../../resources/city_100x40.csv")) {
		std::cerr << "Error: cannot load map from file" << std::endl;
		return;
	}
	_map.printMap();

	initializeIntersections();

	for (int i = 0; i < 5; ++i) {
		auto car = std::make_shared<Car>(i + 1);
		car->placeOnMap(_map);
		_entityManager.addEntity(car);
	}

	for (int i = 0; i < 2; ++i) {
		auto pedestrian = std::make_shared<Pedestrian>(2 + i + 1);
		pedestrian->placeOnMap(_map);
		_entityManager.addEntity(pedestrian);
	}

	for (int i = 0; i < 1; ++i) {
		auto bus = std::make_shared<Bus>(2 + 1 + i + 1);
		bus->placeOnMap(_map);
		bus->setRandomRoute(9, _map);
		_entityManager.addEntity(bus);
	}
}

Simulation::Simulation(int cars, int pedestrians, int buses, float cycleTime, int simulationSpeed) : _running(false), _numCars(cars), _numPedestrians(pedestrians), _numBuses(buses), _cycleTime(cycleTime), _simulationSpeed(simulationSpeed)
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

	initializeIntersections();

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

void Simulation::initializeIntersections() {
    for (int y = 0; y < _map.getHeight(); ++y) {
        for (int x = 0; x < _map.getWidth(); ++x) {
            // Sprawdź, czy aktualny kafelek to lewy górny róg skrzyżowania
            if (_map.getTile(x, y) == 4 &&
                _map.getTile(x + 1, y) == 4 &&
                _map.getTile(x, y + 1) == 4 &&
                _map.getTile(x + 1, y + 1) == 4) {
                
                Intersection intersection(15.0f); // Tworzenie skrzyżowania z domyślnym czasem cyklu

                // Wykrywanie świateł wokół skrzyżowania
                std::vector<std::pair<int, int>> lightPositions = {
                    {x, y - 2},     // Góra
                    {x + 1, y - 2}, // Góra (prawa strona)
                    {x, y + 3},     // Dół
                    {x + 1, y + 3}, // Dół (prawa strona)
                    {x - 2, y},     // Lewo
                    {x - 2, y + 1}, // Lewo (dolna strona)
                    {x + 3, y},     // Prawo
                    {x + 3, y + 1}  // Prawo (dolna strona)
                };

                for (const auto& pos : lightPositions) {
                    int nx = pos.first;
                    int ny = pos.second;

                    if (_map.getTile(nx, ny) == 5) { // Jeśli znaleziono światło
                        TrafficLights light(nx, ny); // Ustaw pozycję świateł
                        light.setup(_map);

                        // Przypisz światło do odpowiedniej grupy
                        if (nx == x || nx == x + 1) { // Góra lub dół
                            intersection.addUpDownLight(light);
                        } else if (ny == y || ny == y + 1) { // Lewo lub prawo
                            intersection.addLeftRightLight(light);
                        }
                    }
                }

                _intersections.push_back(intersection); // Dodaj skrzyżowanie do listy
            }
        }
    }
}

void Simulation::run() {
	_running = true;
	const float dt = 1.0;// 1.0f / 60.0f;
	while (_running) {
		update(dt);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Simulation::update(float dt) {
	_entityManager.updateAll(dt, _map);
	for (auto& intersection : _intersections) {
		intersection.update(dt, _map);
	}
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

EntityManager& Simulation::getEntityManager(){
	return _entityManager;
}

std::vector<Intersection>& Simulation::getIntersections(){
	return _intersections;
}

void Simulation::reset() {
	_running = false;
	_entityManager.clearAll();
	_map.resetMap();
	_map.printMap();
	initializeIntersections();
	for (int i = 0; i < _numCars; ++i) {
		auto car = std::make_shared<Car>(i + 1);
		car->placeOnMap(_map);
		_entityManager.addEntity(car);
	}
	for (int i = 0; i < _numPedestrians; ++i) {
		auto pedestrian = std::make_shared<Pedestrian>(_numCars + i + 1);
		pedestrian->placeOnMap(_map);
		_entityManager.addEntity(pedestrian);
	}
	for (int i = 0; i < _numBuses; ++i) {
		auto bus = std::make_shared<Bus>(_numCars + _numPedestrians + i + 1);
		bus->placeOnMap(_map);
		bus->setRandomRoute(9, _map);
		_entityManager.addEntity(bus);
	}
	_running = true;
}

void Simulation::resume() {
	_running = true;
}