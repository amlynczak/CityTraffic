#include"Bus.h"
#include<iostream>

Bus::Bus(int id, float x, float y, float velocity, Direction dir) : Vehicle(id, x, y, dir, velocity), _currentStop(0), _stopTime(0), _atStop(false) {}

void Bus::setRoute(std::vector<std::pair<float, float>> route) {
	_route = route;
}

void Bus::update(float delta) {
	
}