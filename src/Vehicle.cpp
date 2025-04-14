#include "Vehicle.h"
#include<iostream>

void Vehicle::placeOnMap(const Map& map)
{
	srand(time(0)); // Inicjalizacja generatora liczb losowych
	int dir = rand() % 4;
	switch (dir)
	{
	case 0:
		_dir = Direction::UP;
		for (int i = 0; i < map.getWidth()-1; i++) {
			if (map.getTile(i, 0) == 1 && map.getTile(i+1,0)==1) {
				_x = i;
				_y = 0;
				break;
			}
		}
		break;
	case 1:
		_dir = Direction::DOWN;
		for (int i = 0; i < map.getWidth() - 1; i++) {
			if (map.getTile(i, map.getHeight() - 1) == 1 && map.getTile(i + 1, map.getHeight() - 1) != 1) {
				_x = i;
				_y = map.getHeight() - 1;
				break;
			}
		}
		break;
	case 2:
		_dir = Direction::RIGHT;
		for (int i = 0; i < map.getHeight() - 1; i++) {
			if (map.getTile(0, i) == 1 && map.getTile(0, i + 1) != 1) {
				_x = 0;
				_y = i;
				break;
			}
		}
		break;
	case 3:
		_dir = Direction::LEFT;
		for (int i = 0; i < map.getHeight() - 1; i++) {
			if (map.getTile(map.getWidth() - 1, i) == 1 && map.getTile(map.getWidth() - 1, i + 1) == 1) {
				_x = map.getWidth() - 1;
				_y = i;
				break;
			}
		}
		break;
	default:
		_dir = Direction::NONE;
		break;
	}
}

void Vehicle::setSpeed(float speed)
{
	_speed = speed;
}

float Vehicle::getSpeed() const
{
	return _speed;
}