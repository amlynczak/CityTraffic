#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include "TrafficLights.h"
#include "Map.h"

class Intersection {
public:
    Intersection(float cycleTime = 10.f);
    void addUpDownLight(const TrafficLights& light);
    void addLeftRightLight(const TrafficLights& light);
    void update(float deltaTime, Map& map);

    std::vector<TrafficLights>& getUpDownLights();
    std::vector<TrafficLights>& getLeftRightLights();
    std::vector<TrafficLights> getLights() const;

    void setCycleTime(float time);

private:
    std::vector<TrafficLights> UpDownLights;
    std::vector<TrafficLights> LeftRightLights;
    float timer;
    float cycleTime;
    bool upDownGreen;
};

#endif // !INTERSECTION_H
