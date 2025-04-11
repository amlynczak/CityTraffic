#include"Bus.h"
#include<iostream>

Bus::Bus(int id) : Vehicle(id), _currentStop(0), _stopTime(0), _atStop(false) {}

Bus::Bus(int id, float x, float y, float velocity, Direction dir) : Vehicle(id, x, y, dir, velocity), _currentStop(0), _stopTime(0), _atStop(false) {}

void Bus::setRandomRoute(int stops, const Map& map)
{
	_route.clear();
	_currentStop = 0;
	_stopTime = 0;
	_atStop = false;
	for (int i = 0; i < stops; ++i) {
		int x = rand() % map.getWidth();
		int y = rand() % map.getHeight();
		while (map.getTile(x, y) == 1) {
			x = rand() % map.getWidth();
			y = rand() % map.getHeight();
		}
		_route.push_back(std::make_pair(x, y));
		std::cout << "Bus" << _id << " stop " << i << ": (" << x << ", " << y << ")" << std::endl;
	}
}

void Bus::setRoute(std::vector<std::pair<float, float>> route) {
	_route = route;
}

void Bus::update(float delta, const Map& map) {
	if (_atStop) {
		_stopTime += 0.5 * delta;
		if (_stopTime >= 2.0f) { // Stop for 2 seconds
			_atStop = false;
			_stopTime = 0;
			_currentStop++;
			if (_currentStop >= _route.size()) {
				_currentStop = 0; // Loop back to the first stop
			}
		}
		return;
	}

	if (_route.empty()) return;

	auto [targetX, targetY] = _route[_currentStop];
	float dx = targetX - _x;
	float dy = targetY - _y;
	float distance = std::sqrt(dx * dx + dy * dy);

	if (distance < 0.1f) { // If the bus is close enough to the stop
		_atStop = true;
		_stopTime = 0;
		if (_currentStop < _route.size() - 1) {
			_currentStop++;
		}
		else {
			_currentStop = 0; // Loop back to the first stop
		}
		return;
	}

	float moveDistance = 1; // _speed* delta;
	float nextX = _x;
	float nextY = _y;

	switch (_dir)
	{
	case Direction::UP:
		nextY -= moveDistance;
		break;
	case Direction::DOWN:
		nextY += moveDistance;
		break;
	case Direction::RIGHT:
		nextX += moveDistance;
		break;
	case Direction::LEFT:
		nextX -= moveDistance;
		break;
	case Direction::NONE:
		break;
	default:
		break;
	}

	int currentTile = map.getTile((int)_x, (int)_y);
	int nextTile = map.getTile((int)nextX, (int)nextY);

	std::cout << "Bus" << _id << std::endl;
	std::cout << "Current position: (" << _x << ", " << _y << ")" << std::endl;
	std::cout << "Next position: (" << nextX << ", " << nextY << ")" << std::endl;
	std::cout << "Current stop: (" << targetX << ", " << targetY << ")" << std::endl;

	if (nextTile == -1) {
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
		return;
	}

	if (nextTile == 0) {
		this->placeOnMap(map);
		return;
	}

	if (nextTile == 1) {
		_x = nextX;
		_y = nextY;
		return;
	}

	if (nextTile == 2) {
		//TODO: inaczej to trzeba obs³u¿yæ chyba
		this->placeOnMap(map);
		return;
	}

	if (nextTile == 3) {
		_x = nextX;
		_y = nextY;
		return;
	}

    if (nextTile == 4 && currentTile == 3) {  
       _x = nextX;  
       _y = nextY;  
       if (targetX > _x) {  
           _dir = Direction::RIGHT;  
       } else if (targetX < _x) {
           _dir = Direction::LEFT;  
       } else if (targetY > _y) {
           _dir = Direction::DOWN;  
       } else if (targetY < _y) {
           _dir = Direction::UP;  
       } 
	   return;
    }

	if (nextTile == 4 && currentTile == 4) {
		_x = nextX;
		_y = nextY;
		if (targetX < _x) {
			_dir = Direction::LEFT;
		}else if (targetX > _x) {
			_dir = Direction::RIGHT;
		}else if (targetY < _y) {
			_dir = Direction::UP;
		}else if (targetY > _y) {
			_dir = Direction::DOWN;
		}
		return;
	}

	if (nextTile == 5) {
		_x = nextX;
		_y = nextY;
		return;
	}
}