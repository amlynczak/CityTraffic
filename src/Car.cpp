#include"Car.h"
#include<iostream>
#include<stdlib.h>

Car::Car(int id, float x, float y, float speed, Direction dir) : Vehicle(id, x, y, dir, speed) {}

void Car::update(float delta, const Map& map) {
	float ditance = _speed * delta;
	float nextX = _x;
	float nextY = _y;

	switch (_dir)
	{
	case Direction::UP:
		nextY -= ditance;
		break;
	case Direction::DOWN:
		nextY += ditance;
		break;
	case Direction::RIGHT:
		nextX += ditance;
		break;
	case Direction::LEFT:
		nextX -= ditance;
		break;
	default:
		break;
	}

	int tileType = map.getTile(nextX, nextY);
	if (tileType == 1 || tileType == 4 || tileType == 5) {
		_x = nextX;
		_y = nextY;
	}
	
	if (tileType == 4) {
		int turn = rand() % 3; // 0 = prosto, 1 = w lewo, 2 = w prawo
		if (turn == 1) { // Skrêt w lewo
			if (_dir == Direction::UP) _dir = Direction::LEFT;
			else if (_dir == Direction::DOWN) _dir = Direction::RIGHT;
			else if (_dir == Direction::LEFT) _dir = Direction::DOWN;
			else if (_dir == Direction::RIGHT) _dir = Direction::UP;
		}
		else if (turn == 2) { // Skrêt w prawo
			if (_dir == Direction::UP) _dir = Direction::RIGHT;
			else if (_dir == Direction::DOWN) _dir = Direction::LEFT;
			else if (_dir == Direction::LEFT) _dir = Direction::UP;
			else if (_dir == Direction::RIGHT) _dir = Direction::DOWN;
		}
	}
	std::cout << "Car " << _id << tileType << std::endl;
	std::cout << "Car " << _id << " position: " << _x << ", " << _y << std::endl;
}