#include "AlphaStar.h"


//====================================================================================
//This function
//Input:
//Output:
std::vector<int> CalculatePath(Location & from,
							   Location & to,
							   Board & board)
{

	//if we are in player location 
	if (from == to) {
		std::vector<int> path(1);
		path[0] = NONE;
		return path;
	}

	// will store open list of tiles
	std::vector<Tile> open_list;

	// will store closed list of tiles
	std::vector<Tile> closed_list;

	// will store the path
	std::vector<int> path;

	//will store the tiles around our tile
	std::vector<Tile> arround;

	//starting tile
	Tile from_where(from, board.get_char(from),0, (enum Moves)NONE,0);


	//end tile
	Tile to_where(to,board.get_char(from),0, (enum Moves)NONE,0);

	//iterator
	std::vector<Tile>::iterator tile_to_add;

	//push the first tile to the open list
	open_list.push_back(from_where);

	//set the h_score -NEED TO SET h_score based on father
	int h_score = 1;

	int index_of_wanted_tile = 0;

	int index_of_father = 0;
	while (true) {
		//fail safe
		if(open_list.size() == 0 ) {
			std::vector<int> path(1);
			path[0] = NONE;
			return path;
		}

		//reset arround list
		arround.clear();
		//get the index of the tile if the loweest score from the open list
		index_of_wanted_tile = find_the_best_score(open_list);
	
		// add it to the closed list
		closed_list.push_back(open_list[index_of_wanted_tile]);

		//set the iterator to the node we jsut pushed
		tile_to_add = open_list.begin() + index_of_wanted_tile;

		//erase the node from open list
		open_list.erase(tile_to_add);

		//gets all posible tiles around
		get_around(*(closed_list.end()-1), arround, closed_list,board, closed_list.size()-1);

		//calculates theyr score
		calculate_score(arround, to_where.m_location, h_score);

		
		
		int index = 0;
		int tile_in_open = 0;

		//run on all tiles around
		while (index < arround.size()) {

			//check if they are in open
			tile_in_open = check_if_tile_in_vector(arround[index], open_list);

			//if there is no such tile
			if (tile_in_open == -1)
				open_list.push_back(arround[index]);

			//if its in the open list
			else
				//if the f value is better now
				if (arround[index].f_value < open_list[tile_in_open].f_value)
					//update this tile to be in open and remove the prev
					open_list[tile_in_open] = arround[index];
			index++;
		}
		
		
		int ending_tile = check_if_tile_in_vector( to_where, open_list);
		if (ending_tile > -1) {
			closed_list.push_back(open_list[ending_tile]);
			break;
			std::cout << "reached here";
		}

		
		index_of_father++;
	}

	path = make_path(closed_list,from_where);

	return path;
}

//====================================================================================
//getting the tiles arround our tile based on the alogrithm
void get_around(const Tile & curr_tile,
	            std::vector<Tile> & arround,
				const std::vector<Tile> closed_list,
				Board& board,
				int index_of_father)
{

	//getting all 
	init_arround(arround, curr_tile.m_location, board, closed_list, index_of_father);

	//check validity of tiles arround
	if (!check_validity(arround[3], closed_list, board, LEFT))
		arround.erase(arround.begin() + 3);
	if (!check_validity(arround[2], closed_list, board, RIGHT))
		arround.erase(arround.begin() + 2);
	if (!check_validity(arround[1], closed_list, board, DOWN))
		arround.erase(arround.begin() + 1);
	if (!check_validity(arround[0], closed_list, board, UP))
		arround.erase(arround.begin() + 0);
}
//====================================================================================

//====================================================================================
//Initialising the arround list
void init_arround(std::vector<Tile>& arround,
				  const Location & curr_location,
	              const Board & board,
	              const std::vector<Tile> & closed_list,
	              int index_of_father) {

	//get the locations
	Location above(curr_location.row - 1, curr_location.col),
		below(curr_location.row + 1, curr_location.col),
		right_l(curr_location.row, curr_location.col + 1),
		left_l(curr_location.row, curr_location.col - 1);

	//getting chars that surround us
	char top = board.get_char(above),
		right = board.get_char(right_l),
		left = board.get_char(left_l),
		bottom = board.get_char(below);

	//push to list
	arround.push_back(Tile(above, top, index_of_father, (enum Moves)UP, closed_list[index_of_father].h_value + 1));
	arround.push_back(Tile(below, bottom, index_of_father, (enum Moves)DOWN, closed_list[index_of_father].h_value + 1));
	arround.push_back(Tile(right_l, right, index_of_father, (enum Moves)RIGHT, closed_list[index_of_father].h_value + 1));
	arround.push_back(Tile(left_l, left, index_of_father, (enum Moves)LEFT, closed_list[index_of_father].h_value + 1));
}
//====================================================================================

//check validity of a specific move
bool check_validity(Tile curr_tile,
					std::vector<Tile> closed_list,
					Board & board,
					enum Moves move)
{

	//if we found the tile in the closed list already
	int tile_in_closed = check_if_tile_in_vector(curr_tile, closed_list);

	if (tile_in_closed != -1)
		return false;

	///if we reached player
	if (curr_tile.m_value == '@')
		return true;

	//if we are in a wall no need to check
	if (curr_tile.m_value == '#')
		return false;

	//will need later
	char below = board.get_char(curr_tile.m_location.row + 1, curr_tile.m_location.col);
	char above = board.get_char(curr_tile.m_location.row -1, curr_tile.m_location.col);
	

	switch (move) {
		case LEFT:
			if (curr_tile.m_value == '#')
				return false;

			else if (below == ' ' && curr_tile.m_value != '-')
				return false;
			return true;
			break;

		case RIGHT:
			//if there is wall  to the right
			if (curr_tile.m_value == '#')
				return false;

			else if (below == ' ' && curr_tile.m_value != '-') 
					return false;
			
			return true;
			break;

		case UP:
			if (curr_tile.m_value == 'H' || (below == 'H' && curr_tile.m_value == ' ' ))
				return true;

			return false;
			break;

		case DOWN:
			if (curr_tile.m_value == '#')
				return false;

			return true;
			break;
	}

	//if we passed all checks
	return true;
}
//====================================================================================


//calculates the f score based on g and h
void calculate_score(std::vector<Tile> & arround,
					 const Location & to,
					 int h_score)
{
	int size = arround.size();
	int index = 0;

	//runing on around tiles
	while (index < size) {
		arround[index].h_value = h_score;
		arround[index].g_value = calculate_g_value(arround[index].m_location, to);
		arround[index].f_value = arround[index].h_value + arround[index].g_value;
		index++;
	}
}
//====================================================================================

//calculating g value based on manhattan algorithm
int calculate_g_value(const Location& from, const Location& to)
{
	return abs((from.row - to.row)) + abs(from.col - to.col);
}
//====================================================================================

//cehck if a specific tile in a vector BASED ON LOCATION
int check_if_tile_in_vector(Tile tile, std::vector<Tile> open_list) {
	int size = open_list.size();

	int index = 0;

	while (index < size) {

		if (tile.m_location == open_list[index].m_location) {
			return index;
		}

		++index;
	}

	return -1;
}
//====================================================================================
//find the tile with the best score
int find_the_best_score(std::vector<Tile> open_list) {
	Tile new_tile;
	size_t end_of_open = open_list.size();
	new_tile = open_list[end_of_open -1];

	int index = 0;
	int tile_index = end_of_open-1;
	int size = open_list.size();

	while (index < size )
	{
		if (new_tile.f_value > open_list[index].f_value) {
			new_tile = open_list[index];
			tile_index = index;
		}
		index++;
	}

	index--;

	return tile_index;

}


//====================================================================================
//makes path out of a closed list
std::vector <int> make_path(std::vector < Tile> closed, Tile to) {
	int index = 0;
	std::vector <int> path ;
	Tile curr_tile = *(closed.end()-1);
	int index_of_father = curr_tile.m_father;

	while (closed[index_of_father].m_location != (*(closed.begin())).m_location) {

		path.insert(path.begin(), closed[index_of_father].m_move);

		index_of_father = closed[index_of_father].m_father;

	}
	if(closed.size() == 2)
		path.insert(path.begin(), closed[1].m_move);

	//path.insert(path.begin(), closed[index_of_father].m_move);

		return path;
}

