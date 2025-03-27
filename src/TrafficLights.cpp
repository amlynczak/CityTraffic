#include "TrafficLights.h"
#include<iostream>

TrafficLights::TrafficLights() : state(LightState::RED), timer(0.0f) {}

void TrafficLights::setup() {
	state = LightState::RED;
	timer = 0.0f;
}

void TrafficLights::update(float deltaTime) {
	timer += deltaTime;
	if (state == LightState::RED && timer > 5.0f) {
		state = LightState::GREEN;
		timer = 0.0f;
	}
	else if (state == LightState::GREEN && timer > 10.0f) {
		state = LightState::YELLOW;
		timer = 0.0f;
	}
	else if (state == LightState::YELLOW && timer > 2.0f) {
		state = LightState::RED;
		timer = 0.0f;
	}
}

LightState TrafficLights::getState() const {
	return state;
}
