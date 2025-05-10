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

    // Initialize Start/Stop and Reset buttons
    _buttonLabels.resize(2);
    _buttonLabels[0].setString("Start/Stop");
    _buttonLabels[1].setString("Reset");

    for (size_t i = 0; i < 2; i++)
    {
        _buttons.push_back(sf::RectangleShape(sf::Vector2f(300.f, 50.f)));
        _buttons[i].setFillColor(sf::Color::Blue);
        _buttons[i].setPosition(1250.f, 125.f + 100.f * i);
        _buttonLabels[i].setFont(_font);
        _buttonLabels[i].setCharacterSize(24);
        _buttonLabels[i].setFillColor(sf::Color::White);
        _buttonLabels[i].setPosition(1250.f, 125.f + 100.f * i);
    }

    // Initialize adjustable parameter buttons
    _adjustableParameters = {
        {"Number of cars", _simulation.getNumCars()},
        {"Number of pedestrians", _simulation.getNumPedestrians()},
        {"Cycle of trafficLights", static_cast<int>(_simulation.getCycleTime())},
        {"Simulation speed", _simulation.getSimulationSpeed()}
    };

    float yOffset = 300.f; // Start below the Reset button
    for (auto& param : _adjustableParameters)
    {
        sf::Text label;
        label.setString(param.first);
        label.setFont(_font);
        label.setCharacterSize(24);
        label.setFillColor(sf::Color::Black);
        label.setPosition(1250.f, yOffset);
        _parameterLabels.push_back(label);

        sf::RectangleShape minusButton(sf::Vector2f(50.f, 50.f));
        minusButton.setFillColor(sf::Color::Blue);
        minusButton.setPosition(1250.f, yOffset + 40.f);
        _minusButtons.push_back(minusButton);

        sf::Text valueText;
        valueText.setString(std::to_string(param.second));
        valueText.setFont(_font);
        valueText.setCharacterSize(24);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(1310.f, yOffset + 50.f);
        _valueTexts.push_back(valueText);

        sf::RectangleShape plusButton(sf::Vector2f(50.f, 50.f));
        plusButton.setFillColor(sf::Color::Blue);
        plusButton.setPosition(1370.f, yOffset + 40.f);
        _plusButtons.push_back(plusButton);

        yOffset += 120.f;
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

            for (size_t i = 0; i < _minusButtons.size(); ++i)
            {
                if (_minusButtons[i].getGlobalBounds().contains(mousePos))
                {
                    adjustParameter(i, -1);
                }
            }

            for (size_t i = 0; i < _plusButtons.size(); ++i)
            {
                if (_plusButtons[i].getGlobalBounds().contains(mousePos))
                {
                    adjustParameter(i, 1);
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

    default:
        break;
    }
}

void GUI::adjustParameter(size_t index, int delta)
{
    if (index < _adjustableParameters.size())
    {
        auto& param = _adjustableParameters[index];
        if(param.second + delta >= 0) // Ensure non-negative values
        {
            param.second += delta;
        }

        // Update the simulation parameter based on the index
        switch (index)
        {
        case 0: // Number of cars
            _simulation.setNumCars(param.second);
            break;
        case 1: // Number of pedestrians
            _simulation.setNumPedestrians(param.second);
            break;
        case 2: // Cycle of traffic lights
            _simulation.setCycleTime(static_cast<float>(param.second));
            break;
        case 3: // Simulation speed
            _simulation.setSimulationSpeed(param.second);
            break;
        default:
            break;
        }
        // Update the corresponding value text
        _valueTexts[index].setString(std::to_string(param.second > 0 ? param.second : 0));
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
                       sf::RectangleShape line(sf::Vector2f(5.f, 20.f));
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
                       sf::RectangleShape line(sf::Vector2f(20.f, 5.f));
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

   for (size_t i = 0; i < _parameterLabels.size(); ++i)
    {
        _window.draw(_parameterLabels[i]);
        _window.draw(_minusButtons[i]);
        _window.draw(_plusButtons[i]);
        _window.draw(_valueTexts[i]);

        sf::Text minusSymbol;
        minusSymbol.setString("-");
        minusSymbol.setFont(_font);
        minusSymbol.setCharacterSize(24);
        minusSymbol.setFillColor(sf::Color::White);
        minusSymbol.setPosition(
            _minusButtons[i].getPosition().x + 15.f, // Wyśrodkowanie w przycisku
            _minusButtons[i].getPosition().y + 10.f
        );

        sf::Text plusSymbol;
        plusSymbol.setString("+");
        plusSymbol.setFont(_font);
        plusSymbol.setCharacterSize(24);
        plusSymbol.setFillColor(sf::Color::White);
        plusSymbol.setPosition(
            _plusButtons[i].getPosition().x + 15.f, // Wyśrodkowanie w przycisku
            _plusButtons[i].getPosition().y + 10.f
        );

        _window.draw(minusSymbol);
        _window.draw(plusSymbol);
    }

   _window.display();
}

