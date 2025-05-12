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
		bus->setRandomRoute(5, _map);
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

	if (!_map.loadFromFile("../../../../resources/city_100x40.csv")) {
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
            if (_map.getTile(x, y) == 4 &&
                _map.getTile(x + 1, y) == 4 &&
                _map.getTile(x, y + 1) == 4 &&
                _map.getTile(x + 1, y + 1) == 4) {
                
                Intersection intersection(15.0f);
                std::vector<std::pair<int, int>> lightPositions = {
                    {x, y - 2},    
                    {x + 1, y - 2},
                    {x, y + 3},    
                    {x + 1, y + 3},
                    {x - 2, y},    
                    {x - 2, y + 1},
                    {x + 3, y},    
                    {x + 3, y + 1} 
                };

                for (const auto& pos : lightPositions) {
                    int nx = pos.first;
                    int ny = pos.second;

                    if (_map.getTile(nx, ny) == 5) {
                        TrafficLights light(nx, ny);
                        light.setup(_map);

                        if (nx == x || nx == x + 1) {
                            intersection.addUpDownLight(light);
                        } else if (ny == y || ny == y + 1) {
                            intersection.addLeftRightLight(light);
                        }
                    }
                }

                _intersections.push_back(intersection);
            }
        }
    }
}

void Simulation::run() {
	_running = true;
}

void Simulation::update(float dt) {
	float adjustedDt = dt * _simulationSpeed;
	_entityManager.updateAll(adjustedDt, _map);
	for (auto& intersection : _intersections) {
		intersection.update(adjustedDt, _map);
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
		bus->setRandomRoute(5, _map);
		_entityManager.addEntity(bus);
	}
	_running = true;
}

void Simulation::resume() {
	_running = true;
}

int Simulation::getNumCars() const{
	   return _numCars;
}

int Simulation::getNumPedestrians() const{
	   return _numPedestrians;
}

int Simulation::getNumBuses() const{
	   return _numBuses;
}

float Simulation::getCycleTime() const{
	   return _cycleTime;
}

int Simulation::getSimulationSpeed() const{
	   return _simulationSpeed;
}

void Simulation::setNumCars(int num) {
	if (num < 0) {
		return;
	}
	else if (num > _numCars) {
		int id = _entityManager.getEntityCount() + 1;
		auto car = std::make_shared<Car>(id);
		car->placeOnMap(_map);
		_entityManager.addEntity(car);
	}
	else if (num < _numCars) {
		int entitiesCount = _entityManager.getEntityCount();
		auto entities = _entityManager.getEntities();
		for(auto it = entities.begin(); it != entities.end(); ++it) {
			if (std::dynamic_pointer_cast<Car>(*it)) {
				int id = (*it)->getId();
				int x = (*it)->getX();
				int y = (*it)->getY();
				_map.getTileObject(x, y).setOccupied(false);
				_entityManager.removeEntity(id);
				break;
			}
		}
	}
	_numCars = num;
}

void Simulation::setNumPedestrians(int num) {
	if (num < 0) {
		return;
	}
	else if (num > _numPedestrians) {
		int id = _entityManager.getEntityCount() + 1;
		auto pedestrian = std::make_shared<Pedestrian>(id);
		pedestrian->placeOnMap(_map);
		_entityManager.addEntity(pedestrian);
	}
	else if (num < _numPedestrians) {
		int entitiesCount = _entityManager.getEntityCount();
		auto entities = _entityManager.getEntities();
		for(auto it = entities.begin(); it != entities.end(); ++it) {
			if (std::dynamic_pointer_cast<Pedestrian>(*it)) {
				int id = (*it)->getId();
				_entityManager.removeEntity(id);
				break;
			}
		}
	}
	_numPedestrians = num;
}

void Simulation::setNumBuses(int num) {
	if (num < 0) {
		return;
	}
	else if (num > _numBuses) {
		int id = _entityManager.getEntityCount() + 1;
		auto bus = std::make_shared<Bus>(id);
		bus->placeOnMap(_map);
		bus->setRandomRoute(5, _map);
		_entityManager.addEntity(bus);
	}
	else if (num < _numBuses) {
		int entitiesCount = _entityManager.getEntityCount();
		auto entities = _entityManager.getEntities();
		for(auto it = entities.begin(); it != entities.end(); ++it) {
			if (std::dynamic_pointer_cast<Bus>(*it)) {
				int id = (*it)->getId();
				int x = (*it)->getX();
				int y = (*it)->getY();
				_map.getTileObject(x, y).setOccupied(false);
				_entityManager.removeEntity(id);
				break;
			}
		}
	}
	_numBuses = num;
}

void Simulation::setCycleTime(float time) {
	if (time <= 0) {
		return;
	}
	for (auto& intersection : _intersections) {
		intersection.setCycleTime(time);
	}
	_cycleTime = time;
}

void Simulation::setSimulationSpeed(int speed) {
	if (speed < 0) {
		return;
	}
	_simulationSpeed = speed;
}