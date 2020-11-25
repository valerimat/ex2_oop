#pragma once 

//======include section======
#include "Location.h"

class Coins 
{
public:
	//c-tor
	Coins(Location& location);

	void relocate(Location& location);
	Location get_location();
private:
	Location m_loctaion;
};