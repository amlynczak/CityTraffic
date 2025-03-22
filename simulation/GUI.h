//
// Created by adamm on 25-03-06.
//

#ifndef GUI_H
#define GUI_H

#include<SFML/Graphics.hpp>

class GUI {
public:
	GUI();
	void run();
private:
	sf::RenderWindow _window;
	sf::RectangleShape rectangle;
	
	void processEvents();
	void update();
	void render();
};

#endif //GUI_H
