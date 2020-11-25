#pragma once

//======include section======
#include "Location.h"
#include <vector>
#include <cstdlib>

class Monster {

public:
	//c-tor
	Monster(Location& location);

	// getters
	Location get_location();
	char get_deleted_it();
	int get_smartnes();

	// setters
	void set_deleted_it(char c);

	// misc
	void relocate(Location& Location);
	void dec_smartnes();
	void reset_smartnes();

	std::vector<int> path;
	
private:
	char m_deleted_it = ' ';
	int m_smartnes;
	int curr_smartnes;
	Location m_location;
};