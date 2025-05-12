#include "Intersection.h"

Intersection::Intersection(float cycleTime) : _timer(0.0f), _cycleTime(cycleTime), _upDownGreen(true) {}

void Intersection::addUpDownLight(const TrafficLights& light) {
    _upDownLights.push_back(light);
}

void Intersection::addLeftRightLight(const TrafficLights& light) {
    _leftRightLights.push_back(light);
}

void Intersection::update(float deltaTime, Map& map) {
    _timer += deltaTime;

    if (_timer >= _cycleTime) {
        _timer = 0.0f;
        _upDownGreen = !_upDownGreen;
    }

    if (_upDownGreen) {
        for (auto& light : _upDownLights) {
            light.setState(LightState::GREEN, map);
        }
        for (auto& light : _leftRightLights) {
            light.setState(LightState::RED, map);
        }
    } else {
        for (auto& light : _leftRightLights) {
            light.setState(LightState::GREEN, map);
        }
        for (auto& light : _upDownLights) {
            light.setState(LightState::RED, map);
        }
    }
}

std::vector<TrafficLights>& Intersection::getUpDownLights(){
    return _upDownLights;
}

std::vector<TrafficLights>& Intersection::getLeftRightLights(){
    return _leftRightLights;
}

std::vector<TrafficLights> Intersection::getLights() const { 
    std::vector<TrafficLights> allLights = _upDownLights;
    allLights.insert(allLights.end(), _leftRightLights.begin(), _leftRightLights.end());
    return allLights;
}

void Intersection::setCycleTime(float time) {
    _cycleTime = time;
}