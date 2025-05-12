#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include "TrafficLights.h"
#include "Map.h"

/**
 * @brief Klasa Intersection, reprezentująca skrzyżowanie na mapie.
 * @details Klasa przechowuje informacje o sygnalizatorach świetlnych w kierunkach góra-dół i lewo-prawo oraz zarządza ich stanem.
 * 
 */
class Intersection {
public:
    /**
     * @brief Konstruktor domyślny, tworzy skrzyżowanie o podanym czasie cyklu.
     * 
     * @param cycleTime Czas cyklu skrzyżowania.
     */
    Intersection(float cycleTime = 10.f);
    /**
     * @brief Funkcja dodająca sygnalizator świetlny w kierunku góra-dół.
     * 
     * @param light Sygnalizator świetlny do dodania.
     */
    void addUpDownLight(const TrafficLights& light);
    /**
     * @brief Funkcja dodająca sygnalizator świetlny w kierunku lewo-prawo.
     * 
     * @param light Sygnalizator świetlny do dodania.
     */
    void addLeftRightLight(const TrafficLights& light);
    /**
     * @brief Funkcja ustawia stan sygnalizatorów świetlnych.
     * 
     * @param state Stan sygnalizatorów świetlnych.
     * @param map Mapa, na której znajdują się sygnalizatory.
     */
    void update(float deltaTime, Map& map);

    /**
     * @brief Funkcja ustawia stan sygnalizatorów świetlnych w kierunku góra-dół.
     * 
     * @param state Stan sygnalizatorów świetlnych.
     * @param map Mapa, na której znajdują się sygnalizatory.
     */
    std::vector<TrafficLights>& getUpDownLights();
    /**
     * @brief Funkcja ustawia stan sygnalizatorów świetlnych w kierunku lewo-prawo.
     * 
     * @param state Stan sygnalizatorów świetlnych.
     * @param map Mapa, na której znajdują się sygnalizatory.
     */
    std::vector<TrafficLights>& getLeftRightLights();
    /**
     * @brief Funkcja zwraca stan sygnalizatorów świetlnych.
     * 
     * @return std::vector<TrafficLights> Stan sygnalizatorów świetlnych.
     */
    std::vector<TrafficLights> getLights() const;
    /**
     * @brief Funkcja ustawia czas cyklu skrzyżowania.
     * 
     * @param time Czas cyklu skrzyżowania.
     */
    void setCycleTime(float time);

private:
    /**
     * @brief Wektor zawierający światła w kierunku góra-dół
     * 
     */
    std::vector<TrafficLights> _upDownLights;
    /**
     * @brief Wektor zawierający światła w kierunku prawo-lewo
     * 
     */
    std::vector<TrafficLights> _leftRightLights;
    /**
     * @brief timer, do odmierzania czasu świateł
     * 
     */
    float _timer;
    /**
     * @brief Czas cyklu skrzyżowania
     * 
     */
    float _cycleTime;
    /**
     * @brief Flaga mówiąca o tym, czy światła w kierunku góra-dół są zielone
     * 
     */
    bool _upDownGreen;
};

#endif // !INTERSECTION_H
