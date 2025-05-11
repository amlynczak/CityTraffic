#ifndef GUI_H
#define GUI_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include"../include/Simulation.h"

/**
 * @brief Klasa GUI, odpowiedzialna za interfejs graficzny symulacji.
 * 
 */
class GUI {
public:
    /**
     * @brief Konstruktor klasy GUI.
     * 
     * @param sim Referencja do obiektu symulacji.
     */
    GUI(Simulation& sim);
    /**
     * @brief Funkcja uruchamiająca główną pętlę programu.
     * 
     */
    void run();
private:
    /**
     * @brief Referencja do obiektu symulacji.
     * 
     */
    Simulation& _simulation;
    /**
     * @brief Obiekt okna renderowania.
     * 
     */
    sf::RenderWindow _window;
    /**
     * @brief Obiekt prostokąta reprezentującego tło przycisków.
     * 
     */
    sf::RectangleShape _buttonsRectangle;
    /**
     * @brief Obiekt tekstu reprezentującego tytuł.
     * 
     */
    sf::Text _title;
    /**
     * @brief Wektor przycisków.
     * 
     */
    std::vector<sf::RectangleShape> _buttons;
    /**
     * @brief Wektor etykiet przycisków.
     * 
     */
    std::vector<sf::Text> _buttonLabels;
    /**
     * @brief Obiekt czcionki.
     * 
     */
    sf::Font _font;
    /**
     * @brief Wektor par reprezentujących parametry do dostosowania.
     * 
     */
    std::vector<std::pair<std::string, int>> _adjustableParameters;
    /**
     * @brief Wektor etykiet parametrów.
     * 
     */
    std::vector<sf::Text> _parameterLabels; 
    /**
     * @brief Wektor przycisków minus.
     * 
     */
    std::vector<sf::RectangleShape> _minusButtons;
    /**
     * @brief Wektor przycisków plus.
     * 
     */
    std::vector<sf::RectangleShape> _plusButtons;
    /**
     * @brief Wektor etykiet wartości parametrów.
     * 
     */ 
    std::vector<sf::Text> _valueTexts; 

    /**
     * @brief Funkcja przetwarzająca zdarzenia.
     * 
     */
    void processEvents();
    /**
     * @brief Funkcja aktualizująca stan GUI.
     * 
     */
    void update();
    /**
     * @brief Funkcja renderująca GUI.
     * 
     */
    void render();
    /**
     * @brief Funkcja obsługująca kliknięcia przycisków.
     * 
     * @param buttonIndex 
     */
    void handleButtonClick(size_t buttonIndex);
    /**
     * @brief Funkcja dostosowująca parametr.
     * 
     * @param index Indeks parametru.
     * @param delta Zmiana wartości parametru.
     */
    void adjustParameter(size_t index, int delta);
};

#endif //GUI_H