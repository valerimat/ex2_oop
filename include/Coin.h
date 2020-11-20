
#pragma once 

#include "Location.h"



class Coins {
public:
	Coins(Location& location);
	void relocate(Location& location);

private:
	Location m_loctaion;

};