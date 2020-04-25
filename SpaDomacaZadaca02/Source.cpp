#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameoflife.h"
#include "render.h"

int main() {
	databomb data;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Gle ti to sunce je izaslo...");
	window.setFramerateLimit(60);
	   
	unsigned int input;
	do {
		std::cout << "Welcome, please choose a display mode:\n  1) Neighboring Colors\n  2) Grouping\n  3) Special Mode\n", std::cin >> input;
		if (input < 1 || input > 3) input = 0;
	} while (!input);
	
	std::array<unsigned int, 2> size = { 100, 100 };
	/*
	unsigned int input, electricboogaloo;
	do {
		std::cout << "\n  1) Default Settings\n  2) Custom Settings", std::cin >> input;
		if (input < 1 || input > 2) input = 0;
		if (input == 2) {
			std::cout << "\n Size (Default - 100, 100): ";
			std::getline(std::cin, line)
		}
	} while (!input);
	*/

	data.window = &window;
	data.clock = &clock;
	data.mode = input;
	data.size = size;
	data.outline = 0.f;
	render frame(data);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		frame.draw();
		window.display();
	}

	return 0;
}