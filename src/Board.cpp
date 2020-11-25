#include "Board.h"
const char enemy = '%';
const char coin = '*';
const char player = '@';

Board::Board()
{

	curr_level = 0;

	std::string   str; // temporary string which we push into the vector;
	std::ifstream file;

	file.open("Board.txt"); // Board.txt has the all levels 

	if (!file)
	{
		std::cout << "File didn't open\n";
		exit(EXIT_FAILURE);
	}

	
	int idex_of_levle = 0;
	while (file.peek() != EOF) {
		std::vector<std::string> m_vector_of_strings; // will hold 2D array of the map and its content
		std::vector<std::string> m_clean_vector_of_strings;

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

			

		}
		// Read the next line from File untill it reaches empty row.
		while (str.size() > 0);

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

;
}


void Board::relload_level() {
	levels[curr_level] = levels_backup[curr_level];
}


// gets the location of the player according to '@' char
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


void Board::load_next_level()
{

	increase_level();

}



// prints the board
void Board::print_board()
{
	for (int i = 0; i < levels[curr_level].size(); i++)
		std::cout << levels[curr_level][i] << std::endl;
}



// gets height
int Board::get_height()
{
	return levels[curr_level].size();
}

// gets width 
int Board::get_width()
{
	return levels[curr_level][0].size();
}

//returns which char there is an a specific location
char Board::get_char(Location location) const {
	return levels[curr_level][location.row][location.col];
}

char Board::get_char(int row, int col) 
{
	return levels[curr_level][row][col];
}

char Board::get_clean_board_char(int row, int col)
{
	return levels_clean[curr_level][row][col];
}

void Board::replace_char(Location &location)
{
	levels[curr_level][location.row][location.col] = levels_clean[curr_level][location.row][location.col];
}

void Board::delete_char(Location& location)
{
	levels[curr_level][location.row][location.col] = ' ';
}

void Board::add_char(Location location, char sign)
{
	levels[curr_level][location.row][location.col] = sign;
}

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




void Board::increase_level()
{
	curr_level +=1;
}



int Board::get_level()
{
	return curr_level+1;
}




bool Board::no_more_levels() {
	if (curr_level == levels.size())
		return true;
	return false;
}