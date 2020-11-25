#pragma once

//======include section======
#include "Location.h"
#include "macros.h"

// Will store tiles for alphaStar algorithm
class Tile
{
public:

	// c-tors
	Tile(Location& location, char value, int index_of_father, enum Moves move, int h_value);
	Tile();

	// operator functions
	bool operator==(Tile& tile) const;
	bool operator!=(Tile& tile) const;

	// members
	
	char m_value;
	int f_value;
	int g_value;
	int h_value;
	int m_father;
    Moves m_move;
	Location m_location;
};




