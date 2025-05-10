#ifndef GUI_H
#define GUI_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include"../include/Simulation.h"

class GUI {
public:
    GUI(Simulation& sim);
    void run();
private:
    Simulation& _simulation;
    sf::RenderWindow _window;
    sf::RectangleShape _buttonsRectangle;
    sf::Text _title;
    std::vector<sf::RectangleShape> _buttons;
    std::vector<sf::Text> _buttonLabels;
    sf::Font _font;

    // New members for adjustable parameters
    std::vector<std::pair<std::string, int>> _adjustableParameters; // Parameter name and value
    std::vector<sf::Text> _parameterLabels; // Labels for parameters
    std::vector<sf::RectangleShape> _minusButtons; // '-' buttons
    std::vector<sf::RectangleShape> _plusButtons;  // '+' buttons
    std::vector<sf::Text> _valueTexts; // Texts displaying current values

    void processEvents();
    void update();
    void render();
    void handleButtonClick(size_t buttonIndex);
    void adjustParameter(size_t index, int delta);

    // New helper method for adjustable parameters
    //void handleAdjustableParameterClick(const sf::Vector2f& mousePos);
};

#endif //GUI_H