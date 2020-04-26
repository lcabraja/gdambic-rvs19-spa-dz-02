#pragma once
#include <vector>
#include <array>

class gameoflife {
	std::vector<std::vector<bool>> field;
	std::vector<std::vector<bool>> checkedField;
	std::array<int, 2> size;

	void randomizeField(float percentage);
	bool random(float percentage);

	// ~~~ brb = bad recursion, brb
	std::vector<std::vector<std::array<int, 2>>> result;
	std::vector<std::array<int, 2>> group;
	void recursiveCheck(std::array<int, 2> coords, int direction);
	void resetCheckField();
public:
	gameoflife(std::array<int, 2> size);
	std::vector<std::vector<bool>> update();
	int countNeighbours(std::array<int, 2>);
	std::vector<std::vector<std::array<int, 2>>> groups();

	std::vector<std::vector<bool>> get_field();
	void set_field(std::vector<std::vector<bool>> field);
};