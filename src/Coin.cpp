#include "Coin.h"


Coins::Coins(Location& location) :m_loctaion(location) {};

void Coins::relocate(Location& location)
{
	m_loctaion = location;
}