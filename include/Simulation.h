//
// Created by adamm on 25-03-06.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include "EntityManager.h"
#include "Map.h"
#include "TrafficLights.h"

class Simulation {
private:
    EntityManager entityManager;
    Map map;
    TrafficLights lights;
    bool running;

public:
    void init();             
    void update(float dt);  
    bool isRunning() const; 
};

#endif //SIMULATION_H
