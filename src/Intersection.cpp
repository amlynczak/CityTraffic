#include "Intersection.h"

Intersection::Intersection(float cycleTime)
    : timer(0.0f), cycleTime(cycleTime) {}

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
    }

    if (timer < cycleTime / 2) {
        for (auto& light : UpDownLights) {
            light.update(deltaTime, map); // Update UpDown lights
        }
        for (auto& light : LeftRightLights) {
            light.update(0, map); // Keep LeftRight lights red
        }
    } else {
        for (auto& light : LeftRightLights) {
            light.update(deltaTime, map); // Update LeftRight lights
        }
        for (auto& light : UpDownLights) {
            light.update(0, map); // Keep UpDown lights red
        }
    }
}