#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Location.h"
#include "Monster.h"
#include "Coin.h"

#pragma once

class Board
{
public:
	Board(); // constructor
	void get_locations(std::vector<Monster> & , std::vector<Coins> &, Location& ); // gets the location of the hero on the map

	int get_height();
	int get_width();


	void print_board();
	void replace_char(Location &location);
	void delete_char(Location &);
	void add_char(Location &, char);

	//returns char based on wanted location
	char get_char(Location& location);
	char get_char(int row, int col);
	char get_clean_board_char(int row, int col);
	std::vector<std::string> get_clean_board();
	//bool is_above_ground();

	

private:
	std::vector<std::string> m_vector_of_strings; // will hold 2D array of the map and its content
	std::vector<std::string> m_clean_vector_of_strings;
};