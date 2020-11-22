#include "AlphaStar.h"



std::vector<int> CalculatePath(Location & from, Location & to, int ranking,  Board & board) {

	// will store open list of tiles
	std::vector<Tile> open_list;

	// will store closed list of tiles
	std::vector<Tile> closed_list;

	// will store the path
	std::vector<int> path;

	//will store the tiles around our tile
	std::vector<Tile> arround;

	//starting tile
	Tile from_where(from, board.get_char(from),0, (enum Moves)NONE);

	//end tile
	Tile end_tile(to,board.get_char(from),0, (enum Moves)NONE);

	//iterator
	std::vector<Tile>::iterator tile_to_add;

	//push the first tile to the open list
	open_list.push_back(from_where);

	//set the h_score -NEED TO SET h_score based on father
	int h_score = 1;

	int index_of_wanted_tile = 0;

	while (true) {
		//get the index of the tile if the loweest score from the open list
		index_of_wanted_tile = find_the_best_score(open_list);

		// add it to the closed list
		closed_list.push_back(open_list[index_of_wanted_tile]);

		//set the iterator to the node we jsut pushed
		tile_to_add = open_list.begin() + index_of_wanted_tile;

		//erase the node from open list
		open_list.erase(tile_to_add);

		//gets all posible tiles around
		get_around(*tile_to_add, arround, closed_list,board, index_of_wanted_tile);

		//calculates theyr score
		calculate_score(arround, end_tile.m_location, h_score);


		int index = 0;
		int tile_in_open = 0;

		//run on all tiles around
		while (index < arround.size()) {

			//check if they are in open
			tile_in_open = check_if_tile_in_open(arround[index], open_list);

			//if there is no such tile
			if (tile_in_open == -1)
				open_list.push_back(arround[index]);

			//if its in the open list
			else
				//if the f value is better now
				if (arround[index].f_value < open_list[tile_in_open].f_value)
					//update this tile to be in open and remove the prev
					open_list[tile_in_open] = arround[index];
		}
		
		
		int ending_tile = ending_tile_in_open(open_list, end_tile);
		if (ending_tile > -1) {
			closed_list.push_back(open_list[ending_tile]);
			break;
		}

		//up h_score
		h_score++;

	}

	path = make_path(closed_list);

	return path;
}



void get_around(const Tile & curr_tile, std::vector<Tile>  & arround, const std::vector<Tile> closed_list, Board& board, int idex_of_father) {

	Location curr_location = curr_tile.m_location;
	//getting all 
	Location above   (curr_location.row - 1, curr_location.col),
			 below   (curr_location.row + 1, curr_location.col),
		     right_l (curr_location.row, curr_location.col + 1),
			 left_l  (curr_location.row , curr_location.col -1);

	//getting chars that surround us
	char top = board.get_char(above),
		 right = board.get_char(right_l),
		 left = board.get_char(left_l),
		 bottom = board.get_char(below);

	
	bool y_axis = true,
	     x_axis = false;
	

	arround.push_back(Tile(above, top, idex_of_father, (enum Moves)UP));
	arround.push_back(Tile(below, bottom, idex_of_father, (enum Moves)DOWN));
	arround.push_back(Tile(right_l, right, idex_of_father, (enum Moves)RIGHT));
	arround.push_back(Tile(left_l, left, idex_of_father, (enum Moves)LEFT));

	int size = arround.size();

	for (int index = 0; index < size; ++index) {

		//if its y axis
		if (index < 2)
			if (!check_validity(arround[index], closed_list, board, y_axis))
				arround.erase(index);

		else
			if(!check_validity(arround[index], closed_list, board, x_axis))
				arround.erase(index);
	}


}


bool check_validity(Tile curr_tile, const std::vector<Tile> closed_list, bool y_axis) {
	
	int size_of_list = closed_list.size();
	int index = 0;

	//checking our tile is not an unpassable object
	if (curr_tile.m_value == Wall_or_Floor) {
		return false;
	}


	//if its top bottom checkitng its ladder
	if (y_axis)
		if (curr_tile.m_value != Ladder) {
			return false;
		}
			

	//checking its not in the clsed list
	while (index < size_of_list) {
		if (curr_tile = closed_list[index]) {
			curr_tile = empty;
			return false;
		}
		++index;
	}

	return true;

}

/*
This function caclulates scores of given tile
*/
void calculate_score( std::vector<Tile> arround, const Location & to, int h_score)
{
	int size = arround.size();
	int index = 0;

	//runing on around tiles
	while (index < size) {
		arround[index].h_value = h_score;
		arround[index].g_value = calculate_g_value(arround[index].m_location, to);
		arround[index].f_value = arround[index].h_value + arround[index].g_value;
	}
}


/*
calculates g value based on manhattan algo
*/
int calculate_g_value(const Location& from, const Location& to)
{
	return abs((from.row - to.row)) + abs(from.col - to.col);
}

/*
check if tile is in open list if yes returns index
*/
int check_if_tile_in_open(Tile tile, const std::vector<Tile>& open_list) {

	int size = open_list.size();

	int index = 0;

	while (index < size) {

		if (tile = open_list[index])
			return index;

		++index;
	}
	
	return -1;

}

int find_the_best_score(std::vector<Tile> openlist) {
	Tile new_tile;

	new_tile = openlist[0];

	int index = 0;
	int tile_index = 0;
	int size = openlist.size();

	while (index < size)
	{
		if (new_tile.f_value > openlist[index].f_value) {
			new_tile = openlist[index];
			tile_index = index;
		}
	
	}
	
	openlist.erase(index);

	return tile_index;

}


/*
check if ending tile in open list
*/
int ending_tile_in_open( std::vector<Tile>& open_list, Tile end_tile) {

	int index = 0;
	int size = open_list.size();

	while (index < size) {
		if (open_list[index].m_location == end_tile.m_location)
			return index;
	}

	return 0;

}


std::vector <int> make_path(std::vector < Tile> closed, Tile to) {
	int index = 0;
	std::vector <int> path ;
	Tile curr_tile = closed.end();
	int index_of_father;

	while (closed[index].m_location != closed.begin()) {

		index_of_father = curr_tile.m_father;

		path.insert( path.begin(), closed[index_of_father].move);


	}
		return path;
}