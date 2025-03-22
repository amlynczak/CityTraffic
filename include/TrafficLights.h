//
// Created by adamm on 25-03-06.
//

#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H

enum class LightState { RED, GREEN, YELLOW };

class TrafficLights {
private:
    LightState state;
    float timer;

public:
    TrafficLights();
    void update(float deltaTime);
    LightState getState() const;
};

#endif //TRAFFICLIGHTS_H
