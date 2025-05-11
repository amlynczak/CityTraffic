#ifndef CAR_H
#define CAR_H

#include"Vehicle.h"

/**
 * @brief Klasa Car, reprezentująca samochód na mapie.
 * @details Klasa dziedziczy po klasie Vehicle i implementuje funkcje do umieszczania samochodu na mapie oraz aktualizacji jego położenia.
 * 
 */
class Car : public Vehicle {
public:
	/**
	 * @brief Konstruktor domyślny, tworzy samochód o podanym identyfikatorze.
	 * @param id Identyfikator samochodu.
	 */
	Car(int id);
	/**
	 * @brief Konstruktor, tworzy samochód o podanym identyfikatorze, położeniu i kierunku.
	 * @param id Identyfikator samochodu.
	 * @param x Położenie X samochodu.
	 * @param y Położenie Y samochodu.
	 * @param dir Kierunek ruchu samochodu.
	 */
	Car(int id, float x, float y, Direction dir);

	/**
	 * @brief Funkcja sprawdzająca, czy samochód może przejechać przez dany kafelek.
	 * 
	 * @param map Mapa, na której znajduje się samochód.
	 * @param nextX Współrzędna X następnego kafelka.
	 * @param nextY Współrzędna Y następnego kafelka.
	 * @return true samochód może przejechać przez kafelek
	 * @return false samochód nie może przejechać przez kafelek
	 */
	bool canTravel(const Map& map, int nextX, int nextY);
	/**
	 * @brief Funkcja aktualizująca położenie samochodu na mapie.
	 * 
	 * @param delta Czas, który upłynął od ostatniej aktualizacji.
	 * @param map Mapa, na której znajduje się samochód.
	 * @details Funkcja aktualizuje położenie samochodu na mapie w zależności od kierunku ruchu.
	 */
	void update(float delta, Map& map) override;
};

#endif //CAR_H
