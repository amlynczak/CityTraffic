#ifndef TILE_H  
#define TILE_H  

#include <iostream>  

enum class TileType {  
   INVALID = -1,  
   EMPTY = 0,  
   ROAD = 1,  
   SIDEWALK = 2,  
   CROSSING = 3,  
   INTERSECTION = 4,  
   LIGHTS = 5  
};  

class Tile {
public:
	Tile(TileType type = TileType::INVALID) : _type(type), _isOccupied(false) {}
	Tile(int type) : _type(static_cast<TileType>(type)), _isOccupied(false) {}
	TileType getType() const { return _type; }
	int getTypeAsInt() const { return static_cast<int>(_type); }
	void setType(TileType type) { _type = type; }
	bool isOccupied() const { return _isOccupied; }
	void setOccupied(bool occupied) { _isOccupied = occupied; }
	bool canPedestrianEnter() const { return _canPedestrianEnter; }
	void setCanPedestrianEnter(bool canEnter) { _canPedestrianEnter = canEnter; }

private:
	TileType _type;
	bool _isOccupied;
	bool _canPedestrianEnter;
};

#endif // !TILE_H
