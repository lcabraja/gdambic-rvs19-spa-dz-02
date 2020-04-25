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

	// ~~~ External Variables
	sf::RenderWindow* window;
	sf::Clock* clock;
	std::array<unsigned int, 2> size;
	unsigned int mode;
	float outline;
	std::vector<std::vector<bool>> fieldValues;

	// ~~~ Internal Variables
	sf::Time gametime;
	sf::Time backgroundtime;
	std::unique_ptr<gameoflife> g;
	std::vector<std::string> textures;
	sf::Texture currentTexture;
	int texture = 0;
	unsigned int waittime = 1000;
	sf::Music music;
	sf::Texture ricky;
	sf::RectangleShape background;
	std::vector<std::vector<sf::RectangleShape>> field;
	std::vector<std::vector<sf::RectangleShape>> latice;

	// ~~~ Private Methods
	void loadTextures();
	void next();
	bool elapsedTime(unsigned int milliseconds, sf::Time& time);
	void createBackground();
	void createFields();
	void updateFields();

public:
	render(databomb data);
	void draw();

	std::array<unsigned int, 2> get_size();
};

