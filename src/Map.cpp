#include "Map.h"
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
		std::vector<Tile> row;
		std::istringstream ss(line);
		std::string tile;
		while (std::getline(ss, tile, ',')) {
			row.push_back(Tile(std::stoi(tile)));
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
			switch (tile.getTypeAsInt())
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
	return _grid[y][x].getTypeAsInt();
}

Tile& Map::getTileObject(int x, int y)
{
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

void Map::resetMap() {
	for (int y = 0; y < _height; ++y) {
		for (int x = 0; x < _width; ++x) {
			_grid[y][x].setOccupied(false);
			if(_grid[y][x].getTypeAsInt() == 2) _grid[y][x].setCanPedestrianEnter(true);
			else _grid[y][x].setCanPedestrianEnter(false);
		}
	}
}