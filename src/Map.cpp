#include"Map.h"
#include<iostream>
#include<fstream>
#include<sstream>

Map::Map() : _width(0), _height(0) {
	std::cout << "Map created!" << std::endl;
}

bool Map::loadFromFile(const std::string& filename) {
	std::cout << "Loading map from file: " << filename << std::endl;
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file " << filename << std::endl;
		return false;
	}

	_grid.clear();
	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;
		std::istringstream ss(line);
		std::string tile;
		while (std::getline(ss, tile, ',')) {
			row.push_back(std::stoi(tile));
		}
		_grid.push_back(row);
	}

	_width = _grid[0].size();
	_height = _grid.size();

	file.close();
	return true;
}

void Map::printMap()const {
	for (const auto& row : _grid) {
		for (const auto& tile : row) {
			switch (tile)
			{
			case 0:
				std::cout << "  ";
				break;
			case 1:
				std::cout << "- ";
				break;
			case 2:
				std::cout << "^ ";
				break;
			case 3:
			case 4:
				std::cout << "X ";
				break;
			case 5:
				std::cout << "O ";
				break;
			default:
				break;
			}
		}
		std::cout << std::endl;
	}
}

int Map::getTile(int x, int y)const {
	if (x < 0 || x >= _width || y < 0 || y >= _height) {
		std::cerr << "Error: invalid tile coordinates: (" << x << ", " << y << ")" << std::endl;
		return -1;
	}
	return _grid[y][x];
}

void Map::setTile(int x, int y, int value) {
	if (x < 0 || x >= _width || y < 0 || y >= _height) {
		std::cerr << "Error: invalid tile coordinates: (" << x << ", " << y << ")" << std::endl;
		return;
	}
	_grid[y][x] = value;
}

int Map::getWidth()const {
	return _width;
}

int Map::getHeight()const {
	return _height;
}

std::vector<std::pair<int, int>> Map::getStartPositions()const {
	std::vector<std::pair<int, int>> positions;
	for (int y = 0; y < _height - 1; ++y) {
		if (_grid[y][0] == 1 && _grid[y+1][0] == 1) {
			positions.push_back({ 0, y + 1 });
		}
	}
	for (int x = 0; x < _width - 1; ++x) {
		if (_grid[0][x] == 1 && _grid[0][x+1] == 1) {
			positions.push_back({ x, 0 });
		}
	}
	for (int y = _height - 1; y > 1; --y) {
		if (_grid[y][_width-1] == 1 && _grid[y - 1][_width-1] == 1) {
			positions.push_back({ _width-1, y+1});
		}
	}
	for (int x = _width - 1; x > 1; --x) {
		if (_grid[_height - 1][x] == 1 && _grid[_height - 1][x - 1] == 1) {
			positions.push_back({ x, _height - 1 });
		}
	}
	return positions;
}