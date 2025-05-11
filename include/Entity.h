#ifndef ENTITY_H
#define ENTITY_H

#include"Map.h"

/**
 * @brief Typ wyliczeniowy Direction, reprezentujący kierunki ruchu.
 * 
 */
enum class Direction { UP, DOWN, RIGHT, LEFT, NONE};

/**
 * @brief Klasa Entity, reprezentująca poruszający się obiekt na mapie.
 * 
 */
class Entity {
public:
	/**
	 * @brief Konstruktor domyślny, tworzy obiekt o podanym identyfikatorze.
	 * @param id Identyfikator obiektu.
	 */
	Entity(int id);
	/**
	 * @brief Konstruktor, tworzy obiekt o podanym identyfikatorze, położeniu i kierunku.
	 * @param id Identyfikator obiektu.
	 * @param x Położenie X obiektu.
	 * @param y Położenie Y obiektu.
	 * @param dir Kierunek ruchu obiektu.
	 */
	Entity(int id, float x, float y, Direction dir);
	/**
	 * @brief Destruktor wirtualny, zwalnia zasoby.
	 * 
	 */
    virtual ~Entity() = default;

	/**
	 * @brief Wirtualna funkcja, która umieszcza obiekt na mapie.
	 * 
	 * @param map Mapa, na której znajduje się obiekt.
	 * @details Wirtualna funkcja, która powinna być zaimplementowana w klasach pochodnych.
	 */
	virtual void placeOnMap(const Map& map) = 0;
	/**
	 * @brief Wirtualna funkcja, która aktualizuje położenie obiektu na mapie.
	 * 
	 * @param delta Czas, który upłynął od ostatniej aktualizacji.
	 * @param map Mapa, na której znajduje się obiekt.
	 * @details Wirtualna funkcja, która powinna być zaimplementowana w klasach pochodnych.
	 */
	virtual void update(float delta, Map& map) = 0;


	/**
	 * @brief Zwraca identyfikator obiektu.
	 * 
	 * @return Identyfikator obiektu.
	 */
	int getId()const;

	/**
	 * @brief Zwraca położenie na osi X obiektu.
	 * 
	 * @return Położenie na osi X obiektu.
	 */
	float getX()const;

	/**
	 * @brief Zwraca położenie na osi Y obiektu.
	 * 
	 * @return Położenie na osi Y obiektu.
	 */
	float getY()const;

protected:
	/**
	 * @brief identifikator obiektu.
	 * 
	 */
    int _id;
	/**
	 * @brief położenie na osi X obiektu.
	 * 
	 */
	float _x;
	/**
	 * @brief położenie na osi Y obiektu.
	 * 
	 */
	float _y;
	/**
	 * @brief kierunek ruchu obiektu.
	 * 
	 */
	Direction _dir;
};

#endif
