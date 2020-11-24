
#pragma once 

#include "Location.h"



class Coins {
public:
	Coins(Location& location);
	void relocate(Location& location);
	Location get_location();
private:
	Location m_loctaion;
};