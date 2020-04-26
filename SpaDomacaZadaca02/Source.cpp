#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameoflife.h"
#include "render.h"

int main() {
	databomb data;
	sf::Clock clock;
	   
	int input;
	do {
		std::cout << "Welcome, please choose a display mode:\n  1) Heatmap -- chooses pixel color based on number of neighbors\n  2) Grouping -- gives neighboring pixels the same color (per frame)\n  3) Special Mode\n  4) White Grid -- white on black\n  ", std::cin >> input;
		if (input < 1 || input > 4) input = 0;
	} while (!input);
	
	std::array<int, 2> size = { 100, 100 };
	/*
	int input, electricboogaloo;
	do {
		std::cout << "\n  1) Default Settings\n  2) Custom Settings", std::cin >> input;
		if (input < 1 || input > 2) input = 0;
		if (input == 2) {
			std::cout << "\n Size (Default - 100, 100): ";
			std::getline(std::cin, line)
		}
	} while (!input);
	*/

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Gle ti to sunce je izaslo...");
	window.setFramerateLimit(60);

	data.window = &window;
	data.clock = &clock;
	data.mode = input;
	data.size = size;
	data.outline = (input == 4 ? 0.5f : 0.f);
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