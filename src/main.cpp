#include "scene/scene.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <pugixml.hpp>
#include <spdlog/spdlog.h>

int main() {
#ifdef DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif // DEBUG
	spdlog::debug("Creating SFML window");
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test title");

	spdlog::debug("Opening test document");
	auto doc = std::make_unique<pugi::xml_document>();
	auto err = doc->load_file("test.xml");
	if (!err) {
		spdlog::error("[XML ERR] {}", err.description());
		return -1;
	}
	auto scene = std::make_unique<st::Scene>(std::move(doc));
	auto ad	   = scene->getActionData();

	if (!ad.has_value()) {
		switch (ad.error()) {
			case st::TreeIDNotSetException:
				spdlog::error("Fatal: one of the scene tree has no ID");
				break;

			case st::EmptyTreeException:
				spdlog::error("Fatal: scene dialog load error");
				break;
		}
		window.close();
		return -1;
	}

	sf::Font font;

	if (!font.loadFromFile("arial.ttf")) {
		spdlog::error("Unable to load main text font");
		return -1;
	}

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(25);
	text.setString(ad.value().currentString);
	text.setFillColor(sf::Color::Red);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Space:
							ad = scene->getActionData();

							if (!ad.has_value()) {
								switch (ad.error()) {
									case st::TreeIDNotSetException:
										spdlog::error("Fatal: one of the scene tree has no ID");
										break;

									case st::EmptyTreeException:
										spdlog::error("Fatal: scene dialog load error");
										break;
								}
								window.close();
								return -1;
							}

							if (ad.value().endOfScene) {
								text.setString("End of Scene - " + ad.value().currentString);
								break;
							}

							text.setString(ad.value().currentString);
							break;
					}
					break;
			}
		}
		window.clear();

		window.draw(text);

		window.display();
	}

	return 0;
}
