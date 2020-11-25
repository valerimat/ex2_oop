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

	void load_next_level();

	void get_locations(std::vector<Monster> & , std::vector<Coins> &, Location&); // gets the location of the hero on the map

	int get_height();
	int get_width();

	void clear_board();

	void print_board();
	void print_board2();
	void replace_char(Location &location);
	void delete_char(Location &);
	void add_char(Location , char);

	//returns char based on wanted location
	char get_char(Location location) const;
	char get_char(int row, int col);
	char get_clean_board_char(int row, int col);
	std::vector<std::string> get_clean_board();
	//bool is_above_ground();
	int get_level();
	bool no_more_levels();
	void relload_level();

private:

	
	void increase_level();
	int curr_level;
	std::vector <std::vector <std::string>> levels;
	std::vector <std::vector <std::string>> levels_backup;
	std::vector <std::vector <std::string>> levels_clean;
};