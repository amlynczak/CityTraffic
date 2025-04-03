#include "Vehicle.h"
#include<iostream>

void Vehicle::placeOnMap(const Map& map)
{
	std::cout << "Placing vehicle on map" << std::endl;
}

void Vehicle::setSpeed(float speed)
{
	_speed = speed;
}

float Vehicle::getSpeed() const
{
	return _speed;
}