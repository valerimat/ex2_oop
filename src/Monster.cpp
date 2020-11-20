#include "Monster.h"



Monster::Monster(Location& location) : m_location(location) {};


void Monster::relocate(Location& location)
{
	m_location = location;
};