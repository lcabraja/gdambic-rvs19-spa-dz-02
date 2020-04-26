#include <array>
#include <ctime>
#include "gameoflife.h"

int gameoflife::countNeighbours(std::array<int, 2> coords)
{
	bool north;
	bool northeast;
	bool east;
	bool southeast;
	bool south;
	bool southwest;
	bool west;
	bool northwest;

	int x = coords[0];
	int y = coords[1];

	if ((y - 1) >= 0) {
		north = field[x][y - 1];
	} else { north = false; }

	if ((y - 1) >= 0 && (x + 1) < size[0]) {
		northeast = field[x + 1][y - 1];
	} else { northeast = false; }

	if ((x + 1) < size[0]) {
		east = field[x + 1][y];
	} else { east = false; }

	if ((y + 1) < size[1] && (x + 1) < size[0]) {
		southeast = field[x + 1][y + 1];
	} else { southeast = false; }

	if ((y + 1) < size[1]) {
		south = field[x][y + 1];
	} else { south = false; }

	if ((y + 1) < size[1] && (x - 1) >= 0) {
		southwest = field[x - 1][y + 1];
	} else { southwest = false; }

	if ((x - 1) >= 0) {
		west = field[x - 1][y];
	} else { west = false; }

	if ((y - 1) >= 0 && (x - 1) >= 0) {
		northwest = field[x - 1][y - 1];
	} else { northwest = false; }

	return
		  (north ? 1 : 0)
		+ (northeast ? 1 : 0)
		+ (east ? 1 : 0)
		+ (southeast ? 1 : 0)
		+ (south ? 1 : 0)
		+ (southwest ? 1 : 0)
		+ (west ? 1 : 0)
		+ (northwest ? 1 : 0);
}

std::vector<std::vector<std::array<int, 2>>> gameoflife::groups()
{
	resetCheckField();
	for (int i = 0; i < size[0]; i++) {
		for (int j = 0; j < size[1]; j++) {
			if (field[i][j] && !checkedField[i][j]) {
				std::array<int, 2> coords = { i, j };
				checkedField[i][j] = true;
				group.push_back(coords);
				recursiveCheck(coords, 0);
				result.push_back(group);
				group.clear();
			}
		}
	}
	return result;
}

void gameoflife::randomizeField(float percentage) {
	for (int i = 0; i < size[0]; i++) {
		std::vector<bool> temp;
		for (int j = 0; j < size[1]; j++) {
			temp.push_back(random(percentage));
		}
		field.push_back(temp);
	}
}

bool gameoflife::random(float percentage) {
	short deciding = rand() % 100;
	if (deciding < (percentage * 100)) return true;
	return false;
}

void gameoflife::recursiveCheck(std::array<int, 2> prevcoords, int direction) {
	bool north;
	bool northeast;
	bool east;
	bool southeast;
	bool south;
	bool southwest;
	bool west;
	bool northwest;
	
	int x = prevcoords[0];
	int y = prevcoords[1];

	if ((y - 1) >= 0 && direction != 5) {
		north = field[x][y - 1];
		if (north && !checkedField[x][y - 1]) {
			checkedField[x][y - 1] = true;
			std::array<int, 2> coords = { x, y - 1 };
			group.push_back(coords);
			recursiveCheck(coords, 3);
		}
	}
	else { north = false; }

	if ((y - 1) >= 0 && (x + 1) < size[0] && direction != 6) {
		northeast = field[x + 1][y - 1];
		if (northeast && !checkedField[x + 1][y - 1]) {
			checkedField[x + 1][y - 1] = true;
			std::array<int, 2> coords = { x + 1, y - 1 };
			group.push_back(coords);
			recursiveCheck(coords, 3);
		}
	}
	else { northeast = false; }

	if ((x + 1) < size[0] && direction != 7) {
		east = field[x + 1][y];
		if (east && !checkedField[x + 1][y]) {
			checkedField[x + 1][y] = true;
			std::array<int, 2> coords = { x + 1, y };
			group.push_back(coords);
			recursiveCheck(coords, 4);
		}
	}
	else { east = false; }

	if ((y + 1) < size[1] && (x + 1) < size[0] && direction != 8) {
		southeast = field[x + 1][y + 1];
		if (southeast && !checkedField[x + 1][y + 1]) {
			checkedField[x + 1][y + 1] = true;
			std::array<int, 2> coords = { x + 1, y + 1 };
			group.push_back(coords);
			recursiveCheck(coords, 4);
		}
	}
	else { southeast = false; }

	if ((y + 1) < size[1] && direction != 1) {
		south = field[x][y + 1];
		if (south && !checkedField[x][y + 1]) {
			checkedField[x][y + 1] = true;
			std::array<int, 2> coords = { x, y + 1 };
			group.push_back(coords);
			recursiveCheck(coords, 1);
		}
	}
	else { south = false; }

	if ((y + 1) < size[1] && (x - 1) >= 0 && direction != 2) {
		southwest = field[x - 1][y + 1];
		if (southwest && !checkedField[x - 1][y + 1]) {
			checkedField[x - 1][y + 1] = true;
			std::array<int, 2> coords = { x - 1, y + 1 };
			group.push_back(coords);
			recursiveCheck(coords, 1);
		}
	}
	else { southwest = false; }

	if ((x - 1) >= 0 && direction != 3) {
		west = field[x - 1][y];
		if (west && !checkedField[x - 1][y]) {
			checkedField[x - 1][y] = true;
			std::array<int, 2> coords = { x - 1, y };
			group.push_back(coords);
			recursiveCheck(coords, 2);
		}
	}
	else { west = false; }

	if ((y - 1) >= 0 && (x - 1) >= 0 && direction != 4) {
		northwest = field[x - 1][y - 1];
		if (northwest && !checkedField[x - 1][y - 1]) {
			checkedField[x - 1][y - 1] = true;
			std::array<int, 2> coords = { x - 1, y - 1 };
			group.push_back(coords);
			recursiveCheck(coords, 2);
		}
	}
	else { northwest = false; }
}

void gameoflife::resetCheckField() {
	std::vector<bool> column;
	column.assign(size[1], false);

	checkedField.clear();
	checkedField.assign(size[0], column);

	result.clear();
	group.clear();
}

gameoflife::gameoflife(std::array<int, 2> size) {
	this->size = size;
	srand(time(nullptr));
	randomizeField(0.25);
}

std::vector<std::vector<bool>> gameoflife::update() {
	std::vector<std::vector<bool>> updatedField;
	for (int i = 0; i < size[0]; i++) {
		std::vector<bool> temp;
		for (int j = 0; j < size[1]; j++) {
			bool newvalue;
			std::array<int, 2> coords = { i, j };
			int neighbours = countNeighbours(coords);
			if (field[i][j]) {
				switch (neighbours) {
				case 0:
				case 1:
					newvalue = false;
					break;
				case 2:
				case 3:
					newvalue = true;
					break;
				default:
					newvalue = false;
					break;
				}
			} else {
				if (neighbours == 3)
					newvalue = true;
				else
					newvalue = false;
			}
			temp.push_back(newvalue);
		}
		updatedField.push_back(temp);
	}
	field = updatedField;
	return updatedField;
}

std::vector<std::vector<bool>> gameoflife::get_field() {
	return field;
}

void gameoflife::set_field(std::vector<std::vector<bool>> field) {
	this->field = field;
}
