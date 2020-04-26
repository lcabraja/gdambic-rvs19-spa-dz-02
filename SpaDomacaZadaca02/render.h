#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <array>
#include "databomb.h"
#include "gameoflife.h"
class render {
	// ~~~ Constants
	float defaultfieldsize = 10.f;
	sf::Color gradient[8] = {
		sf::Color(14, 9, 201, 255),
		sf::Color(25, 229, 236, 255),
		sf::Color(25, 236, 114, 255),
		sf::Color(114, 236, 25, 255),
		sf::Color(236, 204, 25, 255),
		sf::Color(236, 75, 25, 255),
		sf::Color(226, 19, 19, 255),
		sf::Color(255, 216, 216, 255)
	};

	// ~~~ External Variables
	sf::RenderWindow* window;
	sf::Clock* clock;
	std::array<int, 2> size;
	int mode;
	float outline;
	std::vector<std::vector<bool>> fieldValues;

	// ~~~ Internal Variables
	sf::Time gametime;
	sf::Time backgroundtime;
	std::unique_ptr<gameoflife> g;
	std::vector<std::string> textures;
	sf::Texture currentTexture;
	int texture = 0;
	int waittime = 1000;
	sf::Music music;
	sf::Texture ricky;
	sf::RectangleShape background;
	std::vector<std::vector<sf::RectangleShape>> field;
	std::vector<std::vector<sf::RectangleShape>> latice;

	// ~~~ Private Methods
	void loadTextures();
	void next();
	bool elapsedTime(int milliseconds, sf::Time& time);
	void createBackground();
	void createFields();
	void updateFields();

public:
	render(databomb data);
	void draw();

	std::array<int, 2> get_size();
};

