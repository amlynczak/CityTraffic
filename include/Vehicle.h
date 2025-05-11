#ifndef VEHICLE_H
#define VEHICLE_H

#include"Entity.h"

/**
 * @brief Klasa Vehicle, reprezentująca pojazd na mapie.
 * @details Klasa dziedziczy po klasie Entity i implementuje funkcje do umieszczania pojazdu na mapie oraz aktualizacji jego położenia.
 * 
 */
class Vehicle : public Entity{
public:
	/**
	 * @brief Konstruktor domyślny, tworzy pojazd o podanym identyfikatorze.
	 * @param id Identyfikator pojazdu.
	 */
	Vehicle(int id);
	/**
	 * @brief Konstruktor, tworzy pojazd o podanym identyfikatorze, położeniu i kierunku.
	 * @param id Identyfikator pojazdu.
	 * @param x Położenie X pojazdu.
	 * @param y Położenie Y pojazdu.
	 * @param dir Kierunek ruchu pojazdu.
	 */
	Vehicle(int id, float x, float y, Direction dir);
	/**
	 * @brief Destruktor wirtualny, zwalnia zasoby.
	 * 
	 */
	virtual ~Vehicle() = default;

	/**
	 * @brief Funkcja aktualizująca położenie pojazdu na mapie.
	 * 
	 * @param delta Czas, który upłynął od ostatniej aktualizacji.
	 * @param map Mapa, na której znajduje się pojazd.
	 * @details Funkcja aktualizuje położenie pojazdu na mapie w zależności od kierunku ruchu, jest to funkcja wirtualna, należy ją zaimplementować w klasach pochodnych.
	 */
	virtual void update(float delta, Map& map) = 0;
	/**
	 * @brief Umieszcza pojazd na mapie.
	 * @param map Mapa, na której znajduje się pojazd.
	 * @details Funkcja ustawia położenie pojazdu na mapie w zależności od kierunku ruchu, jest to implementacja funkcji wirtualnej z klasy Entity.
	 */
	void placeOnMap(const Map& map) override;
};

#endif