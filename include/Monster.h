#pragma once

#include "Location.h"



class Monster {

public:

	Monster(Location& location);
	void relocate(Location& Location);

private:

	Location m_location;




};