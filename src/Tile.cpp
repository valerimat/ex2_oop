#include "Tile.h"


Tile::Tile(Location& location, char value, int index_of_father, enum Moves move) :
	m_location(location),
	m_value(value),
	f_value(0),
	g_value(0),
	h_value(0),
	m_move(move),
	m_father(index_of_father)
{};

Tile::Tile() :
	m_location(Location(0, 0)),
	m_value('/0'),
	f_value(0),
	g_value(0),
	h_value(0),
	m_father(0),
	m_move(UP)
 {};
