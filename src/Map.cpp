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
			std::cout << tile << " ";
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