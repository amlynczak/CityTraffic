#include "TrafficLights.h"
#include<iostream>

TrafficLights::TrafficLights() : state(LightState::RED), timer(0.0f), x(0), y(0) {}

TrafficLights::TrafficLights(int x, int y) : state(LightState::RED), timer(0.0f), x(x), y(y) {}

void TrafficLights::setup(Map& map) {
	state = LightState::RED;
	map.getTileObject(x, y).setOccupied(true); // Block cars from passing
	timer = 0.0f;
}

void TrafficLights::update(float deltaTime, Map& map) {
	timer += deltaTime;
	if (state == LightState::RED && timer > 12.0f) {
		state = LightState::GREEN;
		map.getTileObject(x, y).setOccupied(false); // Allow cars to pass
		for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Skip the current position
                if (map.getTile(x + dx, y + dy) == 3) {
                    map.getTileObject(x + dx, y + dy).setCanPedestrianEnter(false);
                }
            }
        }
		timer = 0.0f;
	}
	else if (state == LightState::GREEN && timer > 10.0f) {
		state = LightState::YELLOW;
		timer = 0.0f;
		map.getTileObject(x, y).setOccupied(true); // Block cars from passing
	}
	else if (state == LightState::YELLOW && timer > 2.0f) {
		state = LightState::RED;
		timer = 0.0f;
		map.getTileObject(x, y).setOccupied(true); // Block cars from passing
		
		for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Skip the current position
                if (map.getTile(x + dx, y + dy) == 3) {
                    map.getTileObject(x + dx, y + dy).setCanPedestrianEnter(true);
                }
            }
        }
	}
}

LightState TrafficLights::getState() const {
	return state;
}

void TrafficLights::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void TrafficLights::setState(LightState state, Map& map) {
	this->state = state;
	if (state == LightState::RED || state == LightState::YELLOW) {
		map.getTileObject(x, y).setOccupied(true); // Block cars from passing
	}
	else if (state == LightState::GREEN) {
		map.getTileObject(x, y).setOccupied(false); // Allow cars to pass
	}
	timer = 0.0f; // Reset timer when state is set manually
}

int TrafficLights::getX() const {
	return x;
}

int TrafficLights::getY() const {
	return y;
}