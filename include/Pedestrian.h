#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include"Entity.h"

/**
 * @brief Klasa Pedestrian, reprezentująca pieszego na mapie.
 * @details Klasa dziedziczy po klasie Entity i implementuje funkcje do umieszczania pieszego na mapie oraz aktualizacji jego położenia.
 * 
 */
class Pedestrian : public Entity {
public:
	/**
	 * @brief Konstruktor domyślny, tworzy pieszego o podanym identyfikatorze.
	 * @param id Identyfikator pieszego.
	 */
	Pedestrian(int id);
	/**
	 * @brief Konstruktor, tworzy pieszego o podanym identyfikatorze, położeniu i kierunku.
	 * @param id Identyfikator pieszego.
	 * @param x Położenie X pieszego.
	 * @param y Położenie Y pieszego.
	 * @param dir Kierunek ruchu pieszego.
	 */
	Pedestrian(int id, float x, float y, Direction dir);

	/**
	 * @brief Umieszcza pieszego na mapie.
	 * @param map Mapa, na której znajduje się pieszy.
	 * @details Funkcja ustawia położenie pieszego na mapie w zależności od kierunku ruchu, jest to implementacja funkcji wirtualnej z klasy Entity.
	 */
	void placeOnMap(const Map& map) override;

	/**
	 * @brief Aktualizuje położenie pieszego na mapie.
	 * @param delta Czas, który upłynął od ostatniej aktualizacji.
	 * @param map Mapa, na której znajduje się pieszy.
	 * @details Funkcja aktualizuje położenie pieszego na mapie w zależności od kierunku ruchu, jest to implementacja funkcji wirtualnej z klasy Entity.
	 */
	void update(float delta, Map& map) override;
};

#endif //PEDESTRIAN_H
