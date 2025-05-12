#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H

#include "Map.h"

/**
 * @brief Typ wyliczeniowy reprezentujący stan świateł
 * 
 */
enum class LightState { RED, GREEN, YELLOW };

/**
 * @brief Klasa reprezentująca światła drogowe
 * 
 */
class TrafficLights {
public:
    /**
     * @brief Konstruktor domyślny
     * 
     */
    TrafficLights();
    /**
     * @brief Konstruktor z parametrami
     * 
     * @param x Współrzędna x
     * @param y Współrzędna y
     */
    TrafficLights(int x, int y); 
    /**
     * @brief Funkcja ustawiająca stan świateł
     * 
     * @param map Mapa, na której znajdują się światła
     */
    void setup(Map& map);
    /**
     * @brief Funkcja zwracająca stan świateł
     * 
     * @return Stan świateł
     */
    LightState getState() const;
    /**
     * @brief Funkcja ustawiająca stan świateł
     * 
     * @param state Stan, na który mają być ustawione światła
     * @param map Mapa, na której znajdują się światła
     */
    void setState(LightState state, Map& map);
    /**
     * @brief Funkcja zwracająca współrzędną x
     * 
     * @return Współrzędna x
     */
    int getX() const;
    /**
     * @brief Funkcja zwracająca współrzędną y
     * 
     * @return Współrzędna y
     */
    int getY() const;

private:
    /**
     * @brief Stan świateł
     * 
     */
    LightState _state;
    /**
     * @brief Czas trwania stanu świateł
     * 
     */
    float _timer;
    /**
     * @brief Współrzędna x
     * 
     */
    int _x;
    /**
     * @brief Współrzędna y
     * 
     */
	int _y;
};

#endif //TRAFFICLIGHTS_H
