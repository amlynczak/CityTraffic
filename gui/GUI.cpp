//
// Created by adamm on 25-03-06.
//

#include"GUI.h"

GUI::GUI() : _window(sf::VideoMode(1600, 800), "CityTraffic")
{
	if (!_font.loadFromFile("../../../../resources/Overpass-Black.ttf"))
	{
		std::abort();
	}

    _buttonsRectangle.setSize(sf::Vector2f(400.f, 800.f));
    _buttonsRectangle.setFillColor(sf::Color::White);
    _buttonsRectangle.setPosition(1200.f, 0.f);

	_title.setString("CityTraffic");
	_title.setFont(_font);
	_title.setCharacterSize(48);
	_title.setFillColor(sf::Color::Black);
	_title.setPosition(1250.f, 50.f);

	_buttonLabels.resize(6);
	_buttonLabels[0].setString("Start/Stop");
	_buttonLabels[1].setString("Reset");
	_buttonLabels[2].setString("Number of cars");
	_buttonLabels[3].setString("Number of pedestrians");
	_buttonLabels[4].setString("Cycle of trafficLights");
	_buttonLabels[5].setString("Simulation speed");

	for (size_t i = 0; i < _buttonLabels.size(); i++)
	{
		_buttons.push_back(sf::RectangleShape(sf::Vector2f(300.f, 50.f)));
		_buttons[i].setFillColor(sf::Color::Blue);
		_buttons[i].setPosition(1250.f, 150.f + 100.f * i);
		_buttonLabels[i].setFont(_font);
		_buttonLabels[i].setCharacterSize(24);
		_buttonLabels[i].setFillColor(sf::Color::White);
		_buttonLabels[i].setPosition(1250.f, 150.f + 100.f * i);
	}


}

void GUI::run()
{
    while (_window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void GUI::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
}

void GUI::update()
{
    
}

void GUI::render()
{
    _window.clear();
    _window.draw(_buttonsRectangle);
	_window.draw(_title);

	for (const auto& button : _buttons) _window.draw(button);
	for (const auto& label : _buttonLabels) _window.draw(label);

    _window.display();
}
