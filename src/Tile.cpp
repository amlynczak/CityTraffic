#include "Tile.h"

Tile::Tile(TileType type = TileType::INVALID) : _type(type), _isOccupied(false){
	_canPedestrianEnter = (type == TileType::SIDEWALK);
}

Tile::Tile(int type) : _type(static_cast<TileType>(type)), _isOccupied(false) {
	_canPedestrianEnter = (type == static_cast<int>(TileType::SIDEWALK));
}

TileType Tile::getType() const { 
	return _type; 
}

int Tile::getTypeAsInt() const {
	return static_cast<int>(_type); 
}

void Tile::setType(TileType type) {
	_type = type; 
}

bool Tile::isOccupied() const {
	return _isOccupied; 
}

void Tile::setOccupied(bool occupied) {
	_isOccupied = occupied; 
}

bool Tile::canPedestrianEnter() const {
	return _canPedestrianEnter; 
}

void Tile::setCanPedestrianEnter(bool canEnter) {
	_canPedestrianEnter = canEnter; 
}