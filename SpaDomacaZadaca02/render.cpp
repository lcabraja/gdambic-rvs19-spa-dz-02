#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <array>
#include <ctime>
#include "render.h"
#include "gameoflife.h"

void render::loadTextures() {
	std::ifstream textures("resources/ricky/filenames.txt");
	std::string line;
	while (getline(textures, line)) {
		this->textures.push_back(line);
	}
	currentTexture.loadFromFile(this->textures[texture]);
}

void render::next() {
	if (++texture >= textures.size())
		texture = 0;

	currentTexture.loadFromFile(textures[texture]);
}

bool render::elapsedTime(unsigned int milliseconds, sf::Time& time) {
	if ((clock->getElapsedTime().asMilliseconds() - time.asMilliseconds()) > milliseconds) {
		time = clock->getElapsedTime();
		return true;
	}
	
	return false;
}

void render::createBackground() {
	auto windowsize = window->getSize();
	background.setSize(sf::Vector2f((float)windowsize.x, (float)windowsize.y));

	if (mode == 3) {
		background.setFillColor(sf::Color().White);
		background.setTexture(&currentTexture);
	} else { background.setFillColor(sf::Color().Black); }
}

void render::createFields()
{
	auto windowsize = window->getSize();
	float fieldsizex = (float)windowsize.x / size[0];
	float fieldsizey = (float)windowsize.y / size[1];

	for (int i = 0; i < size[0]; i++) {
		std::vector<sf::RectangleShape> temp;
		for (int j = 0; j < size[1]; j++) {
			sf::RectangleShape temptangle(sf::Vector2f(fieldsizex, fieldsizey));
			temptangle.setOutlineThickness(outline);
			temptangle.setPosition(sf::Vector2f(fieldsizex * i, fieldsizey * j));
			if (fieldValues[i][j]) {
				temptangle.setFillColor(sf::Color().White);
			}
			else {
				temptangle.setFillColor(sf::Color().Transparent);
			}
			temp.push_back(temptangle);
		}
		field.push_back(temp);
	}

	if (mode == 2) {
		auto result = g->groups();
		for (int i = 0; i < result.size(); i++) {
			sf::Color groupcolor((64 + rand() % 191), (64 + rand() % 191), (64 + rand() % 191), 255);
			for (int j = 0; j < result[i].size(); j++) {
				field[result[i][j][0]][result[i][j][1]].setFillColor(groupcolor);
			}
		}
	}
}

void render::updateFields() {
	if (mode == 2) {
		auto result = g->groups();
		for (int i = 0; i < size[0]; i++)
			for (int j = 0; j < size[1]; j++)
					field[i][j].setFillColor(sf::Color().Transparent);
		for (int i = 0; i < result.size(); i++) {
			sf::Color groupcolor((64 + rand() % 191), (64 + rand() % 191), (64 + rand() % 191), 255);
			for (int j = 0; j < result[i].size(); j++) {
				field[result[i][j][0]][result[i][j][1]].setFillColor(groupcolor);
			}
		}
	}
	else {
		for (int i = 0; i < size[0]; i++)
			for (int j = 0; j < size[1]; j++)
				if (fieldValues[i][j])
					field[i][j].setFillColor(sf::Color().White);
				else
					field[i][j].setFillColor(sf::Color().Transparent);
	}
}

render::render(databomb data) {
	window = data.window;
	clock = data.clock;
	mode = data.mode;
	size = data.size;
	outline = data.outline;

	gametime = clock->getElapsedTime();
	srand(time(nullptr));

	if (mode == 3) {
		backgroundtime = clock->getElapsedTime();
		loadTextures();
		music.openFromFile("resources/ricky/ricky.wav");
	}

	createBackground();

	g.reset(new gameoflife(get_size()));
	fieldValues = g->get_field();
	createFields();
}

void render::draw() {
	if (elapsedTime(waittime, gametime)) {
		fieldValues = g->update();
		updateFields();
		if (mode == 3) 
			if (music.getStatus() != sf::SoundSource::Status::Playing) 
				music.play();
	}

	if (mode == 3)
		if (elapsedTime(200, backgroundtime))
			next();

	window->draw(background);
	for (int i = 0; i < size[0]; i++)
		for (int j = 0; j < size[1]; j++)
			window->draw(field[i][j]);
}

std::array<unsigned int, 2> render::get_size() {
	return size;
}
