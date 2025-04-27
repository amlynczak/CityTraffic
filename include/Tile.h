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
	Tile(TileType type = TileType::INVALID);
	Tile(int type);

	TileType getType() const;
	int getTypeAsInt() const;
	void setType(TileType type);
	bool isOccupied() const;
	void setOccupied(bool occupied);
	bool canPedestrianEnter() const;
	void setCanPedestrianEnter(bool canEnter);

private:
	TileType _type;
	bool _isOccupied;
	bool _canPedestrianEnter;
};

#endif // !TILE_H
