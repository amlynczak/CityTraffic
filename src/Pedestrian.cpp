#include"Pedestrian.h"
#include<iostream>

Pedestrian::Pedestrian(int id) : Entity(id) {}

Pedestrian::Pedestrian(int id, float x, float y, Direction dir) : Entity(id, x, y, dir) {}

void Pedestrian::placeOnMap(const Map& map) {
	int dir = rand() % 4;
	switch (dir)
	{
	case 0:
		_dir = Direction::UP;
		for (int i = 0; i < map.getWidth(); i++) {
			if (map.getTile(i, 0) == 2) {
				_x = i;
				_y = 0;
				break;
			}
		}
		break;
	case 1:
		_dir = Direction::DOWN;
		for (int i = 0; i < map.getWidth(); i++) {
			if (map.getTile(i, map.getHeight() - 1) == 2) {
				_x = i;
				_y = map.getHeight() - 1;
				break;
			}
		}
		break;
	case 2:
		_dir = Direction::RIGHT;
		for (int i = 0; i < map.getHeight(); i++) {
			if (map.getTile(0, i) == 2) {
				_x = 0;
				_y = i;
				break;
			}
		}
		break;
	case 3:
		_dir = Direction::LEFT;
		for (int i = 0; i < map.getHeight(); i++) {
			if (map.getTile(map.getWidth() - 1, i) == 2) {
				_x = map.getWidth() - 1;
				_y = i;
				break;
			}
		}
		break;
	}
}

void Pedestrian::update(float delta, const Map& map) {
	float distance = 1;
	int nextX = _x;
	int nextY = _y;

	switch (_dir)
	{
	case Direction::UP:
		nextY -= distance;
		break;
	case Direction::DOWN:
		nextY += distance;
		break;
	case Direction::RIGHT:
		nextX += distance;
		break;
	case Direction::LEFT:
		nextX -= distance;
		break;
	default:
		break;
	}

	int tileType = map.getTile(nextX, nextY);
	if (tileType == 2) {
		_x = nextX;
		_y = nextY;
	}

	if (tileType == 3 && map.getTile((int)_x, (int)_y) == 2) {
		int turn = rand() % 3; // 0 = prosto, 1 = w lewo, 2 = w prawo
		if (turn == 0) { // Prosto
			if (_dir == Direction::UP) _y = nextY - 1;
			else if (_dir == Direction::DOWN) _y = nextY + 1;
			else if (_dir == Direction::LEFT) _x = nextX - 1;
			else if (_dir == Direction::RIGHT) _x = nextX + 1;
		}
		else if (turn == 1) { // Skrêt w lewo
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
		return;
	}

	if (tileType == -1) {
		switch (_dir)
		{
		case Direction::UP:
			_dir = Direction::DOWN;
			break;
		case Direction::DOWN:
			_dir = Direction::UP;
			break;
		case Direction::RIGHT:
			_dir = Direction::LEFT;
			break;
		case Direction::LEFT:
			_dir = Direction::RIGHT;
			break;
		}
		return;
	}
	if (tileType == 5 || tileType == 1) {
		switch (_dir)
		{
		case Direction::UP:
			_dir = Direction::RIGHT;
			break;
		case Direction::DOWN:
			_dir = Direction::LEFT;
			break;
		case Direction::RIGHT:
			_dir = Direction::UP;
			break;
		case Direction::LEFT:
			_dir = Direction::DOWN;
			break;
		case Direction::NONE:
			break;
		default:
			break;
		}
		return;
	}

	this->setX(nextX);
	this->setY(nextY);

	std::cout << "Pedestrian" << _id << " " << tileType << std::endl;
	std::cout << "Pedestrian" << _id << " position: " << _x << ", " << _y << std::endl;
}