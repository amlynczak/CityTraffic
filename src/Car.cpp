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

void Car::update(float delta, Map& map) {
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

	
	int currentTile = map.getTile((int)_x, (int)_y);
	Tile& currentTileObj = map.getTileObject((int)_x, (int)_y);
	int nextTile = map.getTile(nextX, nextY);

	std::cout << "CAR" << _id << std::endl;
	std::cout << "Current tile: " << currentTile << std::endl;
	std::cout << "Next tile: " << nextTile << std::endl;

	if (nextTile == -1) {
		currentTileObj.setOccupied(false);
		switch (_dir)
		{
		case Direction::UP:
			_x--;
			_dir = Direction::DOWN;
			break;
		case Direction::DOWN:
			_x++;
			_dir = Direction::UP;
			break;
		case Direction::RIGHT:
			_y--;
			_dir = Direction::LEFT;
			break;
		case Direction::LEFT:
			_y++;
			_dir = Direction::RIGHT;
			break;
		case Direction::NONE:
			break;
		default:
			break;
		}
		map.getTileObject((int)_x, (int)_y).setOccupied(true);
		return;
	}

	Tile& nextTileObj = map.getTileObject((int)nextX, (int)nextY);
	if (nextTileObj.isOccupied()) {
		std::cout << "Car " << _id << " is already on the tile!" << std::endl;
		return;
	}

	if (nextTile == 0) {
		this->placeOnMap(map);
		return;
	}

	if (nextTile == 1) {
		currentTileObj.setOccupied(false);
		_x = nextX;
		_y = nextY;
		nextTileObj.setOccupied(true);
		return;
	}

	if (nextTile == 2) {
		//TODO: inaczej to trzeba obs³u¿yæ chyba
		this->placeOnMap(map);
		return;
	}

	if (nextTile == 3) {
		currentTileObj.setOccupied(false);
		_x = nextX;
		_y = nextY;
		nextTileObj.setOccupied(true);
		return;
	}

	if (nextTile == 4 && currentTile == 3) {
		currentTileObj.setOccupied(false);
		_x = nextX;
		_y = nextY;
		nextTileObj.setOccupied(true);
		int turn = rand() % 2; // 0 = prosto, 1 = w prawo
		if (turn == 0) { // Prosto
			return;
		}
		else if (turn == 1) { // Skrêt w prawo
			if (_dir == Direction::UP) _dir = Direction::RIGHT;
			else if (_dir == Direction::DOWN) _dir = Direction::LEFT;
			else if (_dir == Direction::LEFT) _dir = Direction::UP;
			else if (_dir == Direction::RIGHT) _dir = Direction::DOWN;
		}
	}

	if (nextTile == 4 && currentTile == 4) {
		currentTileObj.setOccupied(false);
		_x = nextX;
		_y = nextY;
		nextTileObj.setOccupied(true);
		int turn = rand() % 2; // 0 = prosto, 1 = w lewo
		if (turn == 0) { // Prosto
			return;
		}
		else if (turn == 1) { // Skrêt w lewo
			if (_dir == Direction::UP) _dir = Direction::LEFT;
			else if (_dir == Direction::DOWN) _dir = Direction::RIGHT;
			else if (_dir == Direction::LEFT) _dir = Direction::DOWN;
			else if (_dir == Direction::RIGHT) _dir = Direction::UP;
		}
	}

	if (nextTile == 5) {
		currentTileObj.setOccupied(false);
		_x = nextX;
		_y = nextY;
		nextTileObj.setOccupied(true);
		return;
	}
}