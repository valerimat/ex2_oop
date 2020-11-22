#pragma once
#include "Location.h"
#include "macros.h"

// Will store tiles for alphaStar algorithm
class Tile {
public:
	Tile(Location& location, char value, int index_of_father, enum Moves move, int h_value);
	Tile();

	bool operator==(Tile& tile) const;
	bool operator!=(Tile& tile) const;

	Location m_location;
	char m_value;
	int f_value;
	int g_value;
	int h_value;
	int m_father;
    Moves m_move;
};




