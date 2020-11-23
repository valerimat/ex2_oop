#pragma once

#include "Location.h"
#include <vector>
#include <cstdlib>

class Monster {

public:

	Monster(Location& location);
	void relocate(Location& Location);
	Location get_location();
	void dec_smartnes();
	std::vector<int> path;
	int get_smartnes();
	void reset_smartnes();
	char get_deleted_it();
	void set_deleted_it(char c);
private:

	char m_deleted_it = ' ';
	int m_smartnes;
	int curr_smartnes;
	Location m_location;




};