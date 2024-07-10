#include <cstdio>
#include <string>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test title");
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close(); break;
            }

        }
        window.clear();

        window.draw(shape);

        window.display();
    }

    return 0;
}
