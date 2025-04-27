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
        upDownGreen = !upDownGreen; // Switch active lights
    }

    if (upDownGreen) {
        for (auto& light : UpDownLights) {
            light.setState(LightState::GREEN, map); // Force UpDown lights to green
            //light.update(deltaTime, map);     // Update logic for green lights
        }
        for (auto& light : LeftRightLights) {
            light.setState(LightState::RED, map);  // Force LeftRight lights to red
            //light.update(0, map);             // No update needed for red lights
        }
    } else {
        for (auto& light : LeftRightLights) {
            light.setState(LightState::GREEN, map); // Force LeftRight lights to green
            //light.update(deltaTime, map);     // Update logic for green lights
        }
        for (auto& light : UpDownLights) {
            light.setState(LightState::RED, map);  // Force UpDown lights to red
            //light.update(0, map);             // No update needed for red lights
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