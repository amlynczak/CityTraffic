#ifndef MAP_H
#define MAP_H

#include<string>
#include<vector>

class Map {
public:
	Map();

    bool loadFromFile(const std::string& filename);
    void printMap()const;

	int getTile(int x, int y)const;
	void setTile(int x, int y, int value);
	int getWidth()const;
	int getHeight()const;

	std::vector<std::pair<int, int>> getStartPositions()const;

private:
	std::vector<std::vector<int>> _grid;
	int _width;
	int _height;
};

#endif //MAP_H
