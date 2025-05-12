#include "TrafficLights.h"
#include<iostream>

TrafficLights::TrafficLights() : state(LightState::RED), timer(0.0f), x(0), y(0) {}

TrafficLights::TrafficLights(int x, int y) : state(LightState::RED), timer(0.0f), x(x), y(y) {}

void TrafficLights::setup(Map& map) {
	state = LightState::RED;
	map.getTileObject(x, y).setOccupied(true);
	timer = 0.0f;
}

LightState TrafficLights::getState() const {
	return state;
}

void TrafficLights::setState(LightState state, Map& map) {
	this->state = state;
	if (state == LightState::RED || state == LightState::YELLOW) {
		map.getTileObject(x, y).setOccupied(true);
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) continue;
				if (map.getTile(x + dx, y + dy) == 3) {
					map.getTileObject(x + dx, y + dy).setCanPedestrianEnter(true);
				}
			}
		}
	}
	else if (state == LightState::GREEN) {
		map.getTileObject(x, y).setOccupied(false);
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) continue;
				if (map.getTile(x + dx, y + dy) == 3) {
					map.getTileObject(x + dx, y + dy).setCanPedestrianEnter(false);
				}
			}
		}
	}
	timer = 0.0f;
}

int TrafficLights::getX() const {
	return x;
}

int TrafficLights::getY() const {
	return y;
}