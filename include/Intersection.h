#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include "TrafficLights.h"
#include "Map.h"

class Intersection {
private:
    std::vector<TrafficLights> UpDownLights;
    std::vector<TrafficLights> LeftRightLights;
    float timer;
    float cycleTime;
public:
    Intersection(float cycleTime = 10.f);
    void addUpDownLight(const TrafficLights& light); // Add light to UpDown group
    void addLeftRightLight(const TrafficLights& light); // Add light to LeftRight group
    void update(float deltaTime, Map& map); // Update the state of the lights
};

#endif // !INTERSECTION_H
