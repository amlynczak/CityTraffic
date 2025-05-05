//
// Created by adamm on 25-03-06.
//

#include"GUI.h"
#include"../include/Car.h"
#include"../include/Bus.h"
#include"../include/Pedestrian.h"

GUI::GUI(Simulation& sim) : _window(sf::VideoMode(1600, 800), "CityTraffic"), _simulation(sim)
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

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            for (size_t i = 0; i < _buttons.size(); ++i)
            {
                if (_buttons[i].getGlobalBounds().contains(mousePos))
                {
                    handleButtonClick(i);
                }
            }
        }
    }
}

void GUI::handleButtonClick(size_t buttonIndex)
{
    switch (buttonIndex)
    {
    case 0: // Start/Stop
        if (_simulation.isRunning())
            _simulation.stop();
        else
            _simulation.run();
        break;

    case 1: // Reset
        _simulation.reset(); // Przykładowe wartości: 5 samochodów, 2 pieszych, 1 autobus, cykl 15s, prędkość 1x
        break;

    case 2: // Number of cars
        // Zwiększ liczbę samochodów w symulacji
        break;

    case 3: // Number of pedestrians
        // Zwiększ liczbę pieszych w symulacji
        break;

    case 4: // Cycle of trafficLights
        // Zmień cykl świateł
        break;

    case 5: // Simulation speed
        // Zmień prędkość symulacji
        break;

    default:
        break;
    }
}



void GUI::update() {
    static sf::Clock clock;
    float dt = 0.1;//clock.restart().asSeconds();
    _simulation.update(dt);  // tylko je�li chcesz symulacj� odpala� st�d
}


void GUI::render()
{
   _window.clear();

   // 1. Rysuj map� (siatk�)
   const Map& map = _simulation.getMap();
   for (int y = 0; y < map.getHeight(); ++y)
   {
       for (int x = 0; x < map.getWidth(); ++x)
       {
           sf::RectangleShape tile(sf::Vector2f(20.f, 20.f));
           tile.setPosition(x * 20.f, y * 20.f);

           switch (map.getTile(x, y)) {
           case 0: tile.setFillColor(sf::Color(50, 200, 50)); break; // trawa
           case 1: 
               tile.setFillColor(sf::Color(100, 100, 100)); // jezdnia

               // Sprawdzenie poziomego pasa
               if (x + 1 < map.getWidth() &&
                   map.getTile(x, y) == 1 && map.getTile(x + 1, y) == 1 &&
                   (x == 0 || map.getTile(x - 1, y) != 1) &&
                   (x + 2 >= map.getWidth() || map.getTile(x + 2, y) != 1))
               {
                   if ((x + y) % 2 == 0) {
                       sf::RectangleShape line(sf::Vector2f(2.f, 20.f));
                       line.setFillColor(sf::Color(220, 220, 220));
                       line.setPosition(x * 20.f + 10.f, y * 20.f);
                       _window.draw(line);
                   }
               }

               // Sprawdzenie pionowego pasa
               if (y + 1 < map.getHeight() &&
                   map.getTile(x, y) == 1 && map.getTile(x, y + 1) == 1 &&
                   (y == 0 || map.getTile(x, y - 1) != 1) &&
                   (y + 2 >= map.getHeight() || map.getTile(x, y + 2) != 1))
               {
                   if ((x + y) % 2 == 0) {
                       sf::RectangleShape line(sf::Vector2f(20.f, 2.f));
                       line.setFillColor(sf::Color(220, 220, 220));
                       line.setPosition(x * 20.f, y * 20.f + 10.f);
                       _window.draw(line);
                   }
               }

               break; // jezdnia
           case 2: tile.setFillColor(sf::Color(200, 200, 200)); break; // chodnik
           case 3: tile.setFillColor(sf::Color(100, 100, 100)); break; // przej�cie dla pieszych
           case 4: tile.setFillColor(sf::Color(100, 100, 100)); break; // skrzy�owanie
           default: tile.setFillColor(sf::Color::Black); break;
           }

           _window.draw(tile);
       }
   }

   // 2. Rysuj encje (samochody itd.)
   const auto& entities = _simulation.getEntityManager().getEntities();
   for (const auto& entity : entities)
   {
       sf::RectangleShape e(sf::Vector2f(20.f, 20.f));
       e.setPosition(entity->getX() * 20.f, entity->getY() * 20.f);

       if (dynamic_cast<Car*>(entity.get())) {
           e.setSize(sf::Vector2f(15.f, 15.f)); // Samoch�d
           e.setFillColor(sf::Color::Blue);
       }
       else if (dynamic_cast<Bus*>(entity.get())) {
           e.setSize(sf::Vector2f(20.f, 20.f)); // Autobus
           e.setFillColor(sf::Color::Red);
       }
       else if (dynamic_cast<Pedestrian*>(entity.get())) {
           e.setSize(sf::Vector2f(10.f, 10.f)); // Pieszy
           e.setFillColor(sf::Color::Yellow);
       }
       else
           e.setFillColor(sf::Color::Magenta);

       _window.draw(e);
   }

   for (const auto& intersection : _simulation.getIntersections()) {
    for (const auto& light : intersection.getLights()) {
        sf::CircleShape lightCircle(5.f);
        lightCircle.setPosition(light.getX() * 20.f + 7.5f, light.getY() * 20.f + 7.5f);

        switch (light.getState()) {
        case LightState::RED:
            lightCircle.setFillColor(sf::Color::Red);
            break;
        case LightState::YELLOW:
            lightCircle.setFillColor(sf::Color::Yellow);
            break;
        case LightState::GREEN:
            lightCircle.setFillColor(sf::Color::Green);
            break;
        }

        _window.draw(lightCircle);
    }
}

   // 4. GUI interfejs
   _window.draw(_buttonsRectangle);
   _window.draw(_title);
   for (const auto& button : _buttons) _window.draw(button);
   for (const auto& label : _buttonLabels) _window.draw(label);

   _window.display();
}

