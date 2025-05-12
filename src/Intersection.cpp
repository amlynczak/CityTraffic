#include "Intersection.h"

Intersection::Intersection(float cycleTime) : timer(0.0f), cycleTime(cycleTime), upDownGreen(true) {}

void Intersection::addUpDownLight(const TrafficLights& light) {
    UpDownLights.push_back(light);
}

void Intersection::addLeftRightLight(const TrafficLights& light) {
    LeftRightLights.push_back(light);
}

void Intersection::update(float deltaTime, Map& map) {
    timer += deltaTime;

    if (timer >= cycleTime) {
        timer = 0.0f;
        upDownGreen = !upDownGreen;
    }

    if (upDownGreen) {
        for (auto& light : UpDownLights) {
            light.setState(LightState::GREEN, map);
        }
        for (auto& light : LeftRightLights) {
            light.setState(LightState::RED, map);
        }
    } else {
        for (auto& light : LeftRightLights) {
            light.setState(LightState::GREEN, map);
        }
        for (auto& light : UpDownLights) {
            light.setState(LightState::RED, map);
        }
    }
}

std::vector<TrafficLights>& Intersection::getUpDownLights(){
    return UpDownLights;
}

std::vector<TrafficLights>& Intersection::getLeftRightLights(){
    return LeftRightLights;
}

std::vector<TrafficLights> Intersection::getLights() const { 
    std::vector<TrafficLights> allLights = UpDownLights;
    allLights.insert(allLights.end(), LeftRightLights.begin(), LeftRightLights.end());
    return allLights;
}

void Intersection::setCycleTime(float time) {
    cycleTime = time;
}