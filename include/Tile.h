#include "Location.h"
#include "macros.h"

// Will store tiles for alphaStar algorithm
class Tile {
public:
	Tile(Location& , char, int, enum Moves);
	Tile();

	Location m_location;
	char m_value;
	int f_value;
	int g_value;
	int h_value;
	int m_father;
    Moves m_move;
};




