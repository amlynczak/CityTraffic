#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H

#include "Map.h"

enum class LightState { RED, GREEN, YELLOW };

class TrafficLights {
private:
    LightState state;
    float timer;
    int x;
	int y;

public:
    TrafficLights();
    TrafficLights(int x, int y); 
    void setup();
    void update(float deltaTime, Map& map);
    LightState getState() const;

    void setPosition(int x, int y);
    int getX() const;
    int getY() const;
};

#endif //TRAFFICLIGHTS_H
