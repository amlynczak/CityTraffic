#ifndef TILE_H  
#define TILE_H  

/**
 * @brief Klasa wyliczeniowa TileType, reprezentująca różne typy kafelków na mapie.
 * 
 */
enum class TileType {  
   INVALID = -1,  
   EMPTY = 0,  
   ROAD = 1,  
   SIDEWALK = 2,  
   CROSSING = 3,  
   INTERSECTION = 4,  
   LIGHTS = 5  
};  

/**
 * @brief Klasa Tile, reprezentująca kafelek na mapie.
 * 
 */
class Tile {
public:
	/**
	 * @brief Konstruktor domyślny, tworzy kafelek o typie INVALID.
	 */
	Tile(TileType type = TileType::INVALID);
	/**
	 * @brief Konstruktor, tworzy kafelek o podanym typie.
	 * @param type Typ kafelka.
	 */
	Tile(int type);

	/**
	 * @brief Zwraca typ kafelka jako liczbę całkowitą.
	 * @return Typ kafelka jako liczba całkowita.
	 */
	int getTypeAsInt() const;

	/**
	 * @brief Sprawdza, czy kafelek jest zajęty.
	 * @return true, jeśli kafelek jest zajęty, w przeciwnym razie false.
	 */
	bool isOccupied() const;

	/**
	 * @brief Ustawia stan zajętości kafelka.
	 * @param occupied Stan zajętości kafelka.
	 */
	void setOccupied(bool occupied);

	/**
	 * @brief Sprawdza, czy pieszy może wejść na kafelek.
	 * @return true, jeśli pieszy może wejść, w przeciwnym razie false.
	 */
	bool canPedestrianEnter() const;
	
	/**
	 * @brief Ustawia stan, czy pieszy może wejść na kafelek.
	 * @param canEnter Stan, czy pieszy może wejść.
	 */
	void setCanPedestrianEnter(bool canEnter);

private:
	/**
	 * @brief Typ kafelka.
	 */
	TileType _type;
	/**
	 * @brief Stan zajętości kafelka.
	 */
	bool _isOccupied;
	/**
	 * @brief Stan, czy pieszy może wejść na kafelek.
	 */
	bool _canPedestrianEnter;
};

#endif // TILE_H
