#include"Bus.h"
#include<iostream>

Bus::Bus(int id) : Vehicle(id), _currentStop(0), _stopTime(0), _atStop(false), _path() {}

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
		while (map.getTile(x, y) != 1) {
			x = rand() % map.getWidth();
			y = rand() % map.getHeight();
		}
		_route.push_back(std::make_pair(x, y));
		std::cout << "Bus" << _id << " stop " << i << ": (" << x << ", " << y << ")" << std::endl;
	}
	_path = calculatePath(
		{ static_cast<int>(_x), static_cast<int>(_y) },
		{ static_cast<int>(_route[_currentStop].first), static_cast<int>(_route[_currentStop].second) },
		map
	);

}

void Bus::setRoute(std::vector<std::pair<float, float>> route) {
	_route = route;
}

void Bus::update(float delta, Map& map) {
	if (_atStop) {
		_stopTime += delta;
		if (_stopTime >= 2.0f) {
			_atStop = false;
			_stopTime = 0;
			_currentStop++;
			if (_currentStop >= _route.size()) {
				_currentStop = 0;
			}

			_path = calculatePath(
				{ static_cast<int>(_x), static_cast<int>(_y) },
				{ static_cast<int>(_route[_currentStop].first), static_cast<int>(_route[_currentStop].second) },
				map
			);

			std::cout << "Bus" << _id << " new path to stop " << _currentStop
				<< ": (" << _route[_currentStop].first << ", " << _route[_currentStop].second << ")" << std::endl;
		}
		return;
	}

	if (_path.empty()) {
		std::cout << "Bus" << _id << ": No path to follow!" << std::endl;
		return;
	}

	auto [targetX, targetY] = _path.front();
	int currentX = static_cast<int>(_x);
	int currentY = static_cast<int>(_y);

	int dx = targetX - currentX;
	int dy = targetY - currentY;

	int nextX = currentX;
	int nextY = currentY;

	if (dx != 0) {
		nextX += (dx > 0) ? 1 : -1;
		_dir = (dx > 0) ? Direction::RIGHT : Direction::LEFT;
	}
	else if (dy != 0) {
		nextY += (dy > 0) ? 1 : -1;
		_dir = (dy > 0) ? Direction::DOWN : Direction::UP;
	}

	int currentTile = map.getTile(currentX, currentY);
	int nextTile = map.getTile(nextX, nextY);
	Tile& nextTileObject = map.getTileObject(nextX, nextY);
	Tile& currentTileObject = map.getTileObject(currentX, currentY);

	if (nextTileObject.isOccupied()) {
		return;
	}

	if (nextTile == 1 || nextTile == 3 || nextTile == 4 || nextTile == 5) {
		currentTileObject.setOccupied(false); // zwolnij aktualny kafelek
		_x = static_cast<float>(nextX);
		_y = static_cast<float>(nextY);
		nextTileObject.setOccupied(true); // zajmij nowy kafelek

		// Jeœli dojechaliœmy dok³adnie do targetX, targetY
		if (nextX == targetX && nextY == targetY) {
			_path.pop(); // punkt osi¹gniêty
			if (_path.empty()) {
				_atStop = true;
				_stopTime = 0;
			}
		}
	}
	else {
		std::cout << "Bus" << _id << ": Blocked at (" << nextX << ", " << nextY << ")" << std::endl;
		// Opcjonalnie: spróbuj przeliczyæ œcie¿kê na nowo lub zostañ w miejscu
	}
}


std::queue<std::pair<int, int>> Bus::calculatePath(std::pair<int, int> startPoint, std::pair<int, int> endPoint, const Map& map) {
	std::queue<std::pair<int, int>> path;
	std::map<std::pair<int, int>, std::pair<int, int>> cameFrom;
	std::set<std::pair<int, int>> visited;
	std::queue<std::pair<int, int>> frontier;

	int width = map.getWidth();
	int height = map.getHeight();

	auto isValid = [&](int x, int y) {
		return x >= 0 && x < width && y >= 0 && y < height &&
			(map.getTile(x, y) == 1 || map.getTile(x, y) == 3 || map.getTile(x, y) == 4 || map.getTile(x, y) == 5);
		};

	// Start BFS
	frontier.push(startPoint);
	visited.insert(startPoint);

	const std::vector<std::pair<int, int>> directions = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	bool reached = false;
	std::pair<int, int> finalPoint;

	while (!frontier.empty() && !reached) {
		auto current = frontier.front();
		frontier.pop();

		// Check if current is within +-1 of endPoint
		if (std::abs(current.first - endPoint.first) <= 1 && std::abs(current.second - endPoint.second) <= 1) {
			finalPoint = current;
			reached = true;
			break;
		}

		// Explore neighbors
		for (auto [dx, dy] : directions) {
			int nx = current.first + dx;
			int ny = current.second + dy;
			std::pair<int, int> next = { nx, ny };

			if (isValid(nx, ny) && visited.find(next) == visited.end()) {
				frontier.push(next);
				visited.insert(next);
				cameFrom[next] = current;
			}
		}
	}

	if (!reached) {
		std::cout << "Bus" << _id << ": No path found!" << std::endl;
		return path;  // empty path
	}

	// Reconstruct path from end to start
	std::vector<std::pair<int, int>> reversePath;
	auto current = finalPoint;
	while (current != startPoint) {
		reversePath.push_back(current);
		current = cameFrom[current];
	}
	std::reverse(reversePath.begin(), reversePath.end());

	for (auto& p : reversePath) {
		path.push(p);
	}

	return path;
}
