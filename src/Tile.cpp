//======include header======
#include "Tile.h"

// c-tor
Tile::Tile(Location& location, char value, int index_of_father, enum Moves move,int h_value) :
	m_location(location),
	m_value(value),
	f_value(0),
	g_value(0),
	h_value(h_value),
	m_move(move),
	m_father(index_of_father)
{};
//----------------------------------------------------------------------------

// c-tor
Tile::Tile() :
	m_location(Location(0, 0)),
	m_value('/0'),
	f_value(0),
	g_value(0),
	h_value(0),
	m_father(0),
	m_move(NONE)
 {};
//----------------------------------------------------------------------------

//operator == on 2 tiles
bool Tile::operator==(Tile& tile) const {
	if (this->m_location == tile.m_location &&
		this->m_value == tile.m_value &&
		this->f_value == tile.f_value &&
		this->g_value == tile.g_value &&
		this->m_move == tile.m_move &&
		this->m_father == tile.m_father)

		return true;

	return false;
};
//----------------------------------------------------------------------------

//operator != on two tiles
bool Tile::operator!=(Tile& tile) const {
	if (this->m_location == tile.m_location &&
		this->m_value == tile.m_value &&
		this->f_value == tile.f_value &&
		this->g_value == tile.g_value &&
		this->m_move == tile.m_move &&
		this->m_father == tile.m_father)

		return false;

	return true;
};
//----------------------------------------------------------------------------