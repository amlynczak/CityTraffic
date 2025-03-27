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
    EntityManager _entityManager;
    Map _map;
    TrafficLights _lights;
    bool _running;

public:
	Simulation();

    void init();  
    void stop();
    void update(float dt);  
    bool isRunning() const; 
};

#endif //SIMULATION_H
