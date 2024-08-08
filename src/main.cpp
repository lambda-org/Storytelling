#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

int main() {
#ifdef DEBUG
  spdlog::set_level(spdlog::level::debug);
#endif // DEBUG
  spdlog::debug("Creating SFML window");

  sf::RenderWindow window(sf::VideoMode(800, 600), "Test title");
  sf::CircleShape shape(50);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      }
    }
    window.clear();

    window.draw(shape);

    window.display();
  }

  return 0;
}
