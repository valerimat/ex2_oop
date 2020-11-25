//======include header======
#include "Coin.h"

//===============C-TORS===============
Coins::Coins(Location& location) :m_loctaion(location) {};
//----------------------------------------------------------------------------

// realocates the coins location
void Coins::relocate(Location& location)
{
	m_loctaion = location;
}
//----------------------------------------------------------------------------

//===============Getters===============

// gets the coin location
Location Coins::get_location()
{
	return m_loctaion;
}
//----------------------------------------------------------------------------