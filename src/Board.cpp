//======include header======
#include "Board.h"

//======const section=======
const char enemy  = '%';
const char coin   = '*';
const char player = '@';

//===============C-TORS===============
Board::Board()
{
	curr_level = 0;

	std::string   str; // temporary string which we push into the vector;
	std::ifstream file;
	std::string   size;

	file.open("Board.txt"); // Board.txt has the all levels 

	if (!file)
	{
		std::cout << "File didn't open\n";
		exit(EXIT_FAILURE);
	}
	char N;
	int idex_of_levle = 0;

	while (file.peek() != EOF)
	{
		std::vector<std::string> m_vector_of_strings; // will hold 2D array of the map and its content
		std::vector<std::string> m_clean_vector_of_strings;
		
		getline(file,size);

		int index = 0;
		do
		{
			//reads each line from the Board.txt
			getline(file, str);

			// Line contains string of length > 0 then save it in vector
			if (str.size() > 0)
			{
				m_vector_of_strings.push_back(str);
				m_clean_vector_of_strings.push_back(str);
			}
			index++;
		}
		// Read the next line from File untill it reaches empty row.
		while (index <= stoi(size));

		levels.push_back(m_vector_of_strings);
		levels_backup.push_back(m_vector_of_strings);

		for (int i = 0; i < m_vector_of_strings.size(); i++)
		{

			for (int j = 0; j < m_vector_of_strings[i].size(); j++)
			{
				if (m_vector_of_strings[i][j] == '@' ||
					m_vector_of_strings[i][j] == '%' ||
					m_vector_of_strings[i][j] == '*')

					m_clean_vector_of_strings[i][j] = ' ';
			}
		}
		levels_clean.push_back(m_clean_vector_of_strings);

		m_vector_of_strings.clear();
		m_clean_vector_of_strings.clear();
	}	
}
//----------------------------------------------------------------------------

// reloads the level again
void Board::relload_level() 
{
	levels[curr_level] = levels_backup[curr_level];
}
//----------------------------------------------------------------------------

//===============Getters===============

// gets the location of the player, all the monster and all the coins
void Board::get_locations(std::vector<Monster> & monsters, std::vector<Coins>  & coins, Location & playerLocation )
{
	Location location(-1, -1); //default size in order to use it
	Coins new_coin(location);
	Monster new_monster(location);

	for (int i = 0; i < levels[curr_level].size(); i++)
	{
		for (int j = 0; j < levels[curr_level][i].size(); j++)
		{
			switch (levels[curr_level][i][j])
			{

			case player:
				location.row = i;
				location.col = j;
				playerLocation = location;
				break;
				
			case coin:
				location.row = i;
				location.col = j;
				new_coin.relocate(location);
				coins.push_back(new_coin);
				break;
				

			case enemy:
				location.row = i;
				location.col = j;
				new_monster.relocate(location);
				monsters.push_back(new_monster);
				break;
			}
		}
	}
}

//----------------------------------------------------------------------------
char Board::return_char_from_default(Location location) const {
	return levels_backup[curr_level][location.row][location.col];
}

// gets height
int Board::get_height()
{
	return levels[curr_level].size();
}
//----------------------------------------------------------------------------

// gets width 
int Board::get_width()
{
	return levels[curr_level][0].size();
}
//----------------------------------------------------------------------------

//returns which char there is an a specific location
char Board::get_char(Location location) const {
	return levels[curr_level][location.row][location.col];
}
//----------------------------------------------------------------------------

// gets a specific char from the main board
char Board::get_char(int row, int col)
{
	return levels[curr_level][row][col];
}
//----------------------------------------------------------------------------

// get a specific char from then clean board
char Board::get_clean_board_char(int row, int col)
{
	return levels_clean[curr_level][row][col];
}
//----------------------------------------------------------------------------

// gets the level
int Board::get_level()
{
	return curr_level + 1;
}
//----------------------------------------------------------------------------


// loads the next level
void Board::load_next_level()
{
	increase_level();
}
//----------------------------------------------------------------------------

// prints the board
void Board::print_board()
{
	for (int i = 0; i < levels[curr_level].size(); i++)
		std::cout << "     " << levels[curr_level][i] << std::endl;
}
//----------------------------------------------------------------------------

// replaces a char with a clean board
void Board::replace_char(Location &location)
{
	levels		[curr_level][location.row][location.col] = 
	levels_clean[curr_level][location.row][location.col];
}
//----------------------------------------------------------------------------

// deletes a char and fill it with a space
void Board::delete_char(Location& location)
{
	levels[curr_level][location.row][location.col] = ' ';
}
//----------------------------------------------------------------------------

// add a specific char into a specific location
void Board::add_char(Location location, char sign)
{
	levels[curr_level][location.row][location.col] = sign;
}
//----------------------------------------------------------------------------

// clears the vector from holding any data 
void Board::clear_board()
{
	for (int i = 0; i < levels[curr_level].size(); i++)
	{
		levels[curr_level][i].clear();
		levels_clean[curr_level][i].clear();
	}

	levels[curr_level].clear();
	levels_clean[curr_level].clear();
}
//----------------------------------------------------------------------------

// increases the level
void Board::increase_level()
{
	curr_level +=1;
}
//----------------------------------------------------------------------------

// checks if there are more levels
bool Board::no_more_levels() {
	if (curr_level +1 == levels.size())
		return true;
	return false;
}
//----------------------------------------------------------------------------