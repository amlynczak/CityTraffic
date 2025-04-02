#include"Car.h"
#include<iostream>
#include<stdlib.h>

Car::Car(int id, float x, float y, float speed, Direction dir) : Vehicle(id, x, y, dir, speed) {}
Car::Car(int id) : Vehicle(id) {}

bool Car::canTravel(const Map& map, int nextX, int nextY) {
	int nextTile = map.getTile(nextX, nextY);
	if (nextTile == 0 || nextTile == 2 || nextTile == -1) return false;
	return true;
}

void Car::update(float delta, const Map& map) {
	float ditance = 1;// _speed* delta;
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
	if (tileType == 1 || tileType == 5) {
		_x = nextX;
		_y = nextY;
	}
	
	if (tileType == 4) {
		int turn = rand() % 3; // 0 = prosto, 1 = w lewo, 2 = w prawo
		if (turn == 0) { // Prosto
			if (_dir == Direction::UP) _y = nextY - 2;
			else if (_dir == Direction::DOWN) _y = nextY + 2;
			else if (_dir == Direction::LEFT) _x = nextX - 2;
			else if (_dir == Direction::RIGHT) _x = nextX + 2;
		}
		else if (turn == 1) { // Skrêt w lewo
			if (_dir == Direction::UP) {
				_x = nextX - 2;
				_y = nextY - 1;
				_dir = Direction::LEFT;
			}
			else if (_dir == Direction::DOWN) {
				_x = nextX + 2;
				_y = nextY + 1;
				_dir = Direction::RIGHT;
			}
			else if (_dir == Direction::LEFT) {
				_x = nextX - 1;
				_y = nextY + 2;
				_dir = Direction::DOWN;
			}
			else if (_dir == Direction::RIGHT) {
				_x = nextX + 1;
				_y = nextY - 2;
				_dir = Direction::UP;
			}
		}
		else if (turn == 2) { // Skrêt w prawo
			if (_dir == Direction::UP) {
				_x = nextX + 1;
				_y = nextY;
				_dir = Direction::RIGHT;
			}
			else if (_dir == Direction::DOWN) {
				_x = nextX - 1;
				_y = nextY;
				_dir = Direction::LEFT;
			}
			else if (_dir == Direction::LEFT) {
				_x = nextX;
				_y = nextY - 1;
				_dir = Direction::UP;
			}
			else if (_dir == Direction::RIGHT) {
				_x = nextX;
				_y = nextY + 1;
				_dir = Direction::DOWN;
			}
		}
	}

	if (tileType == -1) {
		if (_dir == Direction::UP) {
			_x--;
			_dir = Direction::DOWN;
		}
		if (_dir == Direction::DOWN) {
			_x++;
			_dir = Direction::UP;
		}
		if (_dir == Direction::RIGHT) {
			_y--;
			_dir = Direction::LEFT;
		}
		if (_dir == Direction::LEFT) {
			_y++;
			_dir = Direction::RIGHT;
		}
	}
	std::cout << "Car " << _id << tileType << std::endl;
	std::cout << "Car " << _id << " position: " << _x << ", " << _y << std::endl;
}