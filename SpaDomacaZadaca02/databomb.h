#pragma once
#include <SFML/Graphics.hpp>
#include <array>
struct databomb
{
	sf::RenderWindow* window;
	sf::Clock* clock;
	int mode;
	std::array<int, 2> size;
	float outline = 0.f;
};

