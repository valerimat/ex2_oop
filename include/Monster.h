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
	int get_next_path();
	int get_path_size();
	// setters
	void set_deleted_it(char c);
	void set_path(std::vector<int>path);

	// misc
	void relocate(Location& Location);
	void dec_smartnes();
	void reset_smartnes();
	void remove_first_in_path();

private:
	
	//members
	std::vector<int> m_path;
	char m_deleted_it = ' ';
	int m_smartnes;
	int curr_smartnes;
	Location m_location;
};