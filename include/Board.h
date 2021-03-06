#pragma once

//======include section======
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Location.h"
#include "Monster.h"
#include "Coin.h"

class Board
{
public:

	// c-tor
	Board();

	// get functions
	int  get_height() const;
	int  get_width() const;
	char get_char(Location location) const;
	char get_char(int row, int col)const ;
	char get_clean_board_char(int row, int col);
	void get_locations(std::vector<Monster> &, std::vector<Coins> &, Location &); // gets the location of the hero on the map
	int  get_level();

	// board related functions
	void clear_board();
	void print_board();
	bool out_of_boundrie(const Location& location) const;
	

	// level related functions
	void load_next_level();
	bool no_more_levels();
	void relload_level();

	// char related functions
	void add_char(Location, char);
	void replace_char(Location &location);
	void delete_char(Location &);
	char return_char_from_default(Location location) const;

private:
	
	int curr_level;
	std::vector <std::vector <std::string>> levels;
	std::vector <std::vector <std::string>> levels_backup;
	std::vector <std::vector <std::string>> levels_clean;
	void increase_level();
};