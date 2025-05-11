//
// Created by adamm on 25-03-06.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include "EntityManager.h"
#include "Map.h"
#include "TrafficLights.h"
#include "Intersection.h"

/**
 * @brief Klasa Simulation, reprezentująca symulację ruchu drogowego.
 * 
 */
class Simulation {
public:
   /**
    * @brief Konstruktor domyślny.
    * 
    */
   Simulation();
   /**
    * @brief Konstruktor z parametrami.
    * 
    * @param cars Liczba samochodów.
    * @param pedestrians Liczba pieszych.
    * @param buses Liczba autobusów.
    * @param cycleTime Czas cyklu skrzyżowania.
    * @param simulationSpeed Prędkość symulacji.
    */
   Simulation(int cars, int pedestrians, int buses, float cycleTime, int simulationSpeed);
   /**
    * @brief Funkcja inicjalizująca skrzyżowania.
    * 
    */
   void initializeIntersections();
   /**
    * @brief Funkcja uruchamiająca symulację.
    * 
    */
   void run();
   /**
    * @brief Funkcja zatrzymująca symulację.
    * 
    */
   void stop();
   /**
    * @brief Funkcja resetująca symulację.
    * 
    */
   void reset();
   /**
    * @brief Funkcja wznawiająca symulację.
    * 
    */
   void resume();
   /**
    * @brief Funkcja aktualizująca stan symulacji.
    * 
    * @param dt Czas, który upłynął od ostatniej aktualizacji.
    */
   void update(float dt);  
   /**
    * @brief Funkcja zwracająca stan symulacji.
    * 
    * @return true jeśli symulacja jest uruchomiona.
    * @return false jeśli symulacja jest zatrzymana.
    */
   bool isRunning() const;

   /**
    * @brief Funkcja zwracająca liczbę samochodów.
    * 
    * @return Liczba samochodów.
    */
   int getNumCars() const;
   /**
    * @brief Funkcja zwracająca liczbę pieszych.
    * 
    * @return Liczba pieszych.
    */
   int getNumPedestrians() const;
   /**
    * @brief Funkcja zwracająca liczbę autobusów.
    * 
    * @return Liczba autobusów.
    */
   int getNumBuses() const;
   /**
    * @brief Funkcja zwracająca czas cyklu skrzyżowania.
    * 
    * @return Czas cyklu skrzyżowania.
    */
   float getCycleTime() const;
   /**
    * @brief Funkcja zwracająca prędkość symulacji.
    * 
    * @return Prędkość symulacji.
    */
   int getSimulationSpeed() const;

   /**
    * @brief Funkcja ustawiająca liczbę samochodów.
    * 
    * @param num Liczba samochodów.
    */
   void setNumCars(int num);
   /**
    * @brief Funkcja ustawiająca liczbę pieszych.
    * 
    * @param num Liczba pieszych.
    */
   void setNumPedestrians(int num);
   /**
    * @brief Funkcja ustawiająca liczbę autobusów.
    * 
    * @param num Liczba autobusów.
    */
   void setNumBuses(int num);
   /**
    * @brief Funkcja ustawiająca czas cyklu skrzyżowania.
    * 
    * @param time Czas cyklu skrzyżowania.
    */
   void setCycleTime(float time);
   /**
    * @brief Funkcja ustawiająca prędkość symulacji.
    * 
    * @param speed Prędkość symulacji.
    */
   void setSimulationSpeed(int speed);

   /**
    * @brief Funkcja zwracająca mapę.
    * 
    * @return Mapa.
    */
   Map& getMap();
   /**
    * @brief Funkcja zwracająca menedżera obiektów.
    * 
    * @return Menedżer obiektów.
    */
   EntityManager& getEntityManager();
   /**
    * @brief Funkcja zwracająca wektor skrzyżowań.
    * 
    * @return Wektor skrzyżowań.
    */
   std::vector<Intersection>& getIntersections();

private:
   /**
    * @brief Menedżer obiektów, zarządzający poruszającymi się obiektami na mapie.
    * 
    */
   EntityManager _entityManager;
   /**
    * @brief Mapa, na której odbywa się symulacja.
    * 
    */
   Map _map;
   /**
    * @brief Wektor skrzyżowań, na których odbywa się symulacja.
    * 
    */
   std::vector<Intersection> _intersections;
   /**
    * @brief Flaga mówiąca o tym, czy symulacja jest uruchomiona.
    * 
    */
   bool _running;
   /**
    * @brief Liczba samochodów w symulacji.
    * 
    */
   int _numCars;
   /**
    * @brief Liczba pieszych w symulacji.
    * 
    */
   int _numPedestrians;
   /**
    * @brief Liczba autobusów w symulacji.
    * 
    */
   int _numBuses;
   /**
    * @brief Czas cyklu skrzyżowania.
    * 
    */
   float _cycleTime;
   /**
    * @brief Prędkość symulacji.
    * 
    */
   int _simulationSpeed;
};

#endif // SIMULATION_H
