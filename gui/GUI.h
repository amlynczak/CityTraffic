//
// Created by adamm on 25-03-06.
//

#ifndef GUI_H
#define GUI_H

#include<SFML/Graphics.hpp>
#include<vector>

class GUI {
public:
	GUI();
	void run();
private:
	sf::RenderWindow _window;
	sf::RectangleShape _buttonsRectangle;
	sf::Text _title;
	std::vector<sf::RectangleShape> _buttons;
	std::vector<sf::Text> _buttonLabels;
	sf::Font _font;
	
	void processEvents();
	void update();
	void render();
};

#endif //GUI_H
