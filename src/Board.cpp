#include "Board.h"

Board::Board()
{
	std::string   str; // temporary string which we push into the vector;
	std::ifstream file;

	file.open("Board.txt"); // Board.txt has the all levels 

	if (!file)
	{
		std::cout << "File didn't open\n";
		exit(EXIT_FAILURE);
	}

	do
	{
		//reads each line from the Board.txt
		getline(file, str);

		// Line contains string of length > 0 then save it in vector
		if (str.size() > 0)
			m_vector_of_strings.push_back(str);
	}
	// Read the next line from File untill it reaches empty row.
	while (str.size() > 0);
}

// gets the location of the player according to '@' char
Location Board::get_location_of_player()
{
	Location location(-1, -1); //default size in order to use it

	for (int i = 0; i < m_vector_of_strings.size(); i++)
	{
		for (int j = 0; j < m_vector_of_strings[i].size(); j++)
		{
			if (m_vector_of_strings[i][j] == '@')
			{
				location.row = i;
				location.col = j;

				return location;
			}
		}
	}
	return location;
}

// prints the board
void Board::print_board()
{
	for (int i = 0; i < m_vector_of_strings.size(); i++)
		std::cout << m_vector_of_strings[i] << std::endl;
}

// gets height
int Board::get_height()
{
	return m_vector_of_strings.size();
}

// gets width 
int Board::get_width()
{
	return m_vector_of_strings[0].size();
}

bool Board::is_above_ground()
{	
	Location location_player = this->get_location_of_player();
	// checks if there is ground below, which is '#' char in our case
	if (m_vector_of_strings[location_player.row + 1]
						   [location_player.col] == '#')
		return true; // = 1
	
	return false; // = 0
}

// right now it is not fully right, but serves its purpose 
void Board::delete_char(Location& location)
{
	m_vector_of_strings[location.row][location.col] = ' ';
}


void Board::add_char(Location& location, char sign)
{
	m_vector_of_strings[location.row][location.col] = sign;
}