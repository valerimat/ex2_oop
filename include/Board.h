#include <vector>
#include "Location.h"

#pragma once



class Board
{
public:
	Board(); // constructor
	Location get_location_of_player(); // gets the location of the hero on the map
	int get_height();
	int get_width();
	void print_board();

	bool is_above_ground();

private:
	std::vector<std::string> m_vector_of_strings; // will hold 2D array of the map and its content
};