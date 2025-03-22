//
// Created by adamm on 25-03-06.
//

#include"GUI.h"

GUI::GUI() : _window(sf::VideoMode(1600, 800), "CityTraffic")
{
    rectangle.setSize(sf::Vector2f(200.f, 150.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(900.f, 225.f);
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
    _window.draw(rectangle);
    _window.display();
}
