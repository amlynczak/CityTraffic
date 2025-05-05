//
// Created by adamm on 25-03-06.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include "EntityManager.h"
#include "Map.h"
#include "TrafficLights.h"
#include "Intersection.h"

class Simulation {
private:
   EntityManager _entityManager;
   Map _map;
   std::vector<Intersection> _intersections;
   bool _running;

   int _numCars;
   int _numPedestrians;
   int _numBuses;
   float _cycleTime;
   int _simulationSpeed;

public:
   Simulation();
   Simulation(int cars, int pedestrians, int buses, float cycleTime, int simulationSpeed);
   void initializeIntersections();
   void run();
   void stop();
   void reset();
   void resume();
   void update(float dt);  
   bool isRunning() const; 

   Map& getMap();
   EntityManager& getEntityManager();
   std::vector<Intersection>& getIntersections();
};

#endif // SIMULATION_H
