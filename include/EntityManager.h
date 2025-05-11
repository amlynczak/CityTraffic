#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include "Entity.h"

/**
 * @brief Klasa EntityManager, zarządzająca poruszającymi się obiektami na mapie.
 * 
 */
class EntityManager {
public:
	/**
	 * @brief Funkcja dodająca obiekt do zarządzania.
	 * 
	 * @param entity 
	 */
    void addEntity(std::shared_ptr<Entity> entity);
	/**
	 * @brief Funkcja usuwająca obiekt z zarządzania.
	 * 
	 * @param id Identyfikator obiektu do usunięcia.
	 */
	void removeEntity(int id);
	/**
	 * @brief Funkcja usuwająca wszystkie obiekty z zarządzania.
	 * 
	 */
    void clearAll();
	/**
	 * @brief Funkcja aktualizująca wszystkie obiekty na mapie.
	 * 
	 * @param deltaTime Czas, który upłynął od ostatniej aktualizacji.
	 * @param map Mapa, na której znajdują się obiekty.
	 */
    void updateAll(float deltaTime, Map& map);

	/**
	 * @brief Funkcja zwracająca wszystkie obiekty.
	 * 
	 * @return std::vector<std::shared_ptr<Entity>>& Wektor wskaźników do obiektów.
	 */
	std::vector<std::shared_ptr<Entity>>& getEntities();
	/**
	 * @brief Funkcja zwracająca obiekt o podanym identyfikatorze.
	 * 
	 * @param id Identyfikator obiektu.
	 * @return std::shared_ptr<Entity> Wskaźnik do obiektu.
	 */
	std::shared_ptr<Entity> getEntityById(int id);
	/**
	 * @brief Funkcja zwracająca liczbę obiektów.
	 * 
	 * @return int Liczba obiektów.
	 */
	int getEntityCount() const;
private:
	/**
	 * @brief Wektor wskaźników do obiektów.
	 * 
	 */
    std::vector<std::shared_ptr<Entity>> _entities;
};

#endif //ENTITYMANAGER_H
