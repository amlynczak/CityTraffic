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
    std::vector<TrafficLights>& getUpDownLights() { return UpDownLights; } // Get UpDown lights
    std::vector<TrafficLights>& getLeftRightLights() { return LeftRightLights; } // Get LeftRight lights
    std::vector<TrafficLights> getLights() const { 
        std::vector<TrafficLights> allLights = UpDownLights;
        allLights.insert(allLights.end(), LeftRightLights.begin(), LeftRightLights.end());
        return allLights;
    }
};

#endif // !INTERSECTION_H
