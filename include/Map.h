#ifndef MAP_H
#define MAP_H

#include<string>
#include<vector>

#include"Tile.h"

/**
 * @brief Klasa Map, reprezentująca mapę w grze.
 * 
 */
class Map {
public:
	/**
	 * @brief Konstruktor domyślny, tworzy pustą mapę.
	 * 
	 */
	Map();

	/**
	 * @brief Funkcja ładująca mapę z pliku.
	 * 
	 * @param filename Nazwa pliku z mapą.
	 * @return true jeśli mapa została załadowana pomyślnie.
	 * @return false jeśli mapa nie została załadowana pomyślnie.
	 */
    bool loadFromFile(const std::string& filename);
	/**
	 * @brief Wypisuje mapę na standardowe wyjście.
	 * 
	 */
    void printMap()const;

	/**
	 * @brief Zwraca kafelek (reprezentację poprzez int) na podstawie współrzędnych x i y.
	 * 
	 * @param x Współrzędna x
	 * @param y Współrzędna y
	 * @return int reprezentujący typ kafelka
	 */
	int getTile(int x, int y)const;
	/**
	 * @brief Zwraca kafelek (obiekt Tile) na podstawie współrzędnych x i y.
	 * 
	 * @param x Współrzędna x
	 * @param y Współrzędna y
	 * @return Tile reprezentujący kafelek
	 */
	Tile& getTileObject(int x, int y);
	/**
	 * @brief Zwraca szerokość mapy.
	 * 
	 * @return int szerokość mapy
	 */
	int getWidth()const;
	/**
	 * @brief Zwraca wysokość mapy.
	 * 
	 * @return int wysokość mapy
	 */
	int getHeight()const;
	/**
	 * @brief Funkcja resetująca mapę do stanu początkowego.
	 * 
	 */
	void resetMap();

private:
	/**
	 * @brief siatka kafelków reprezentująca mapę.
	 * 
	 */
	std::vector<std::vector<Tile>> _grid;
	/**
	 * @brief szerokość mapy.
	 * 
	 */
	int _width;
	/**
	 * @brief wysokość mapy.
	 * 
	 */
	int _height;
};

#endif // MAP_H
