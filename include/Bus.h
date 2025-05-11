#ifndef BUS_H
#define BUS_H

#include"Vehicle.h";
#include<vector>
#include<utility>
#include<queue>
#include<map>
#include<set>

/**
 * @brief Klasa Bus, reprezentująca autobus na mapie.
 * @details Klasa dziedziczy po klasie Vehicle i implementuje funkcje do umieszczania autobusu na mapie oraz aktualizacji jego położenia.
 * 
 */
class Bus : public Vehicle {
public:
	/**
	 * @brief Konstruktor domyślny, tworzy autobus o podanym identyfikatorze.
	 * @param id Identyfikator autobusu.
	 */
	Bus(int id);
	/**
	 * @brief Konstruktor, tworzy autobus o podanym identyfikatorze, położeniu i kierunku.
	 * @param id Identyfikator autobusu.
	 * @param x Położenie X autobusu.
	 * @param y Położenie Y autobusu.
	 * @param dir Kierunek ruchu autobusu.
	 */
	Bus(int id, float x, float y, Direction dir);

	/**
	 * @brief Funkcja ustawia losową trasę autobusu.
	 * 
	 * @param stops Liczba przystanków na trasie.
	 * @param map Mapa, na której znajduje się autobus.
	 */
	void setRandomRoute(int stops, const Map& map);
	/**
	 * @brief Funkcja ustawia trasę autobusu.
	 * 
	 * @param route Wektor par współrzędnych przystanków na trasie.
	 */
	void setRoute(std::vector<std::pair<float, float>> route);
	/**
	 * @brief Funkcja zwraca trasę autobusu.
	 * 
	 * @return Wektor par współrzędnych przystanków na trasie.
	 */
	std::vector<std::pair<float, float>> getRoute() const;
	/**
	 * @brief Funkcja aktualizująca położenie autobusu na mapie.
	 * 
	 * @param delta Czas, który upłynął od ostatniej aktualizacji.
	 * @param map Mapa, na której znajduje się autobus.
	 * @details Funkcja aktualizuje położenie autobusu na mapie w zależności od kierunku ruchu.
	 */
	void update(float delta, Map& map) override;
	/**
	 * @brief Funkcja obliczająca ścieżkę do przystanku.
	 * 
	 * @param startPoint Punkt początkowy.
	 * @param endPoint Punkt końcowy.
	 * @param map Mapa, na której znajduje się autobus.
	 * @return Kolejka punktów na ścieżce do przystanku.
	 */
	std::queue<std::pair<int, int>> calculatePath(std::pair<int, int> startPoint, std::pair<int, int> endPoint, const Map& map);
private:
	/**
	 * @brief Wektor par współrzędnych przystanków na trasie.
	 * 
	 */
	std::vector<std::pair<float, float>> _route;
	/**
	 * @brief Kolejka punktów na ścieżce do przystanku.
	 * 
	 */
	std::queue<std::pair<int, int>> _path;
	/**
	 * @brief Indeks aktualnego przystanku.
	 * 
	 */
	int _currentStop;
	/**
	 * @brief Czas postoju autobusu na przystanku.
	 * 
	 */
	float _stopTime;
	/**
	 * @brief Flaga informująca, czy autobus jest na przystanku.
	 * 
	 */
	bool _atStop;
};

#endif //BUS_H
