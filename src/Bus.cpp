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
    // Je�li autobus jest na przystanku, odczekaj czas i przejd� do nast�pnego
    if (_atStop) {
        _stopTime += delta;
        if (_stopTime >= 2.0f) { // Zatrzymaj si� na 2 sekundy
            _atStop = false;
            _stopTime = 0;
            _currentStop++;
            if (_currentStop >= _route.size()) {
                _currentStop = 0; // Powr�� do pierwszego przystanku
            }
            // Oblicz now� �cie�k� do kolejnego przystanku
            _path = calculatePath({ _x, _y }, { _route[_currentStop].first, _route[_currentStop].second }, map);
			std::cout << "Bus" << _id << " new path to stop " << _currentStop << ": (" << _route[_currentStop].first << ", " << _route[_currentStop].second << ")" << std::endl;
        }
        return;
    }

    // Je�li nie ma wyznaczonej trasy, nic nie r�b
    if (_path.empty()) return;

    // Pobierz kolejny punkt na trasie
    auto [targetX, targetY] = _path.front();
    _path.pop();  // Usu� punkt z kolejki

    // Je�li autobus jest blisko przystanku, zatrzymaj si�
    float dx = targetX - _x;
    float dy = targetY - _y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 0.1f) { // Je�li autobus jest wystarczaj�co blisko przystanku
        _atStop = true;
        _stopTime = 0;
        return;
    }

    // Oblicz, w kt�r� stron� autobus ma si� porusza�
    float moveDistance = 0.5f * delta;  // Ustalamy pr�dko�� ruchu autobusu w danym czasie

    float nextX = _x;
    float nextY = _y;

    // Poruszanie si� w kierunku X
    if (targetX > _x) {
        nextX += moveDistance;
        _dir = Direction::RIGHT;
    }
    else if (targetX < _x) {
        nextX -= moveDistance;
        _dir = Direction::LEFT;
    }

    // Poruszanie si� w kierunku Y
    if (targetY > _y) {
        nextY += moveDistance;
        _dir = Direction::DOWN;
    }
    else if (targetY < _y) {
        nextY -= moveDistance;
        _dir = Direction::UP;
    }

    // Sprawdzanie, czy autobus mo�e przejecha� przez nast�pny kafelek
    int currentTile = map.getTile((int)_x, (int)_y);
    int nextTile = map.getTile((int)nextX, (int)nextY);  // Poprawka, sprawdzamy kafelek na przysz�ej pozycji

    std::cout << "Bus" << _id << std::endl;
    std::cout << "Current position: (" << _x << ", " << _y << ")" << std::endl;
    std::cout << "Next position: (" << nextX << ", " << nextY << ")" << std::endl;
    std::cout << "Current stop: (" << targetX << ", " << targetY << ")" << std::endl;

    if (nextTile == -1) {  // Je�li napotkano przeszkod�
		this->placeOnMap(map);  // Umie�� autobus na mapie
    }

    // Je�li jest droga (oznaczenie 1, 3, 4, 5), poruszaj si� dalej
    if (nextTile == 1 || nextTile == 3 || nextTile == 4 || nextTile == 5) {
        _x = nextX;  // Uaktualnij pozycj�
        _y = nextY;  // Uaktualnij pozycj�
    }
}



std::queue<std::pair<int, int>> Bus::calculatePath(std::pair<int, int> startPoint, std::pair<int, int> endPoint, const Map& map)
{
	std::queue<std::pair<int, int>> result;  // Kolejka do zwr�cenia �cie�ki
	std::queue<std::pair<int, int>> q;;
	std::map<std::pair<int, int>, std::pair<int, int>> parent;
	std::set<std::pair<int, int>> visited;

	q.push(startPoint);
	visited.insert(startPoint);

	std::vector<std::pair<int, int>> directions = {
		{0, 1}, {1, 0}, {0, -1}, {-1, 0}  // Kierunki: w prawo, w d�, w lewo, w g�r�
	};

	while (!q.empty()) {
		auto [x, y] = q.front(); q.pop();
		if (x == endPoint.first && y == endPoint.second) break;

		for (auto [dx, dy] : directions) {
			int nx = x + dx;
			int ny = y + dy;
			if (map.getTile(nx, ny) != -1) {  // Sprawdzamy, czy wsp�rz�dne s� w obr�bie mapy
				int tile = map.getTile(nx, ny);
				if ((tile == 1 || tile == 3 || tile == 4 || tile == 5) &&  // Sprawdzamy, czy to droga
					visited.find({ nx, ny }) == visited.end()) {
					q.push({ nx, ny });
					visited.insert({ nx, ny });
					parent[{nx, ny}] = { x, y };
				}
			}
		}
	}

	std::pair<int, int> current = endPoint;
	if (parent.find(current) == parent.end()) return result; // Brak �cie�ki, zwracamy pust� kolejk�

	std::vector<std::pair<int, int>> path;
	while (current != startPoint) {
		path.push_back(current);
		current = parent[current];
	}
	path.push_back(startPoint);  // Dodajemy punkt startowy na ko�cu �cie�ki
	std::reverse(path.begin(), path.end());  // Odwracamy �cie�k�, by by�a od startu do ko�ca

	// Dodajemy ka�dy punkt �cie�ki do kolejki
	for (auto& p : path) result.push(p);

	return result;
}
