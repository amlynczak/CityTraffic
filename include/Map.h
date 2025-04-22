#ifndef MAP_H
#define MAP_H

#include<string>
#include<vector>

#include"Tile.h"

class Map {
public:
	Map();

    bool loadFromFile(const std::string& filename);
    void printMap()const;

	int getTile(int x, int y)const;
	Tile& getTileObject(int x, int y);
	void setTile(int x, int y, int value);
	int getWidth()const;
	int getHeight()const;

private:
	std::vector<std::vector<Tile>> _grid;
	int _width;
	int _height;
};

#endif //MAP_H
