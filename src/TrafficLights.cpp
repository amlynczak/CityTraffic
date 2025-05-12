#include "TrafficLights.h"
#include<iostream>

TrafficLights::TrafficLights() : _state(LightState::RED), _timer(0.0f), _x(0), _y(0) {}

TrafficLights::TrafficLights(int x, int y) : _state(LightState::RED), _timer(0.0f), _x(x), _y(y) {}

void TrafficLights::setup(Map& map) {
	_state = LightState::RED;
	map.getTileObject(_x, _y).setOccupied(true);
	_timer = 0.0f;
}

LightState TrafficLights::getState() const {
	return _state;
}

void TrafficLights::setState(LightState state, Map& map) {
	this->_state = state;
	if (state == LightState::RED || state == LightState::YELLOW) {
		map.getTileObject(_x, _y).setOccupied(true);
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) continue;
				if (map.getTile(_x + dx, _y + dy) == 3) {
					map.getTileObject(_x + dx, _y + dy).setCanPedestrianEnter(true);
				}
			}
		}
	}
	else if (state == LightState::GREEN) {
		map.getTileObject(_x, _y).setOccupied(false);
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) continue;
				if (map.getTile(_x + dx, _y + dy) == 3) {
					map.getTileObject(_x + dx, _y + dy).setCanPedestrianEnter(false);
				}
			}
		}
	}
	_timer = 0.0f;
}

int TrafficLights::getX() const {
	return _x;
}

int TrafficLights::getY() const {
	return _y;
}