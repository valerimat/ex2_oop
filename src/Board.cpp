#include "Board.h"
const char enemy = '%';
const char coin = '*';
const char player = '@';


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
		{
			m_vector_of_strings.push_back(str);
			m_clean_vector_of_strings.push_back(str);
		}
			
	}
	// Read the next line from File untill it reaches empty row.
	while (str.size() > 0);

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
}

void Board::load_next_level(Board &board, int level)
{
	std::string   str; // temporary string which we push into the vector;
	std::ifstream file;

	file.open("Board.txt"); // Board.txt has the all levels 

	if (!file)
	{
		std::cout << "File didn't open\n";
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < level; i++)
	{
		clear_board();

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
	}
}

// gets the location of the player according to '@' char
void Board::get_locations(std::vector<Monster> & monsters, std::vector<Coins>  & coins, Location & playerLocation)
{
	Location location(-1, -1); //default size in order to use it
	Coins new_coin(location);
	Monster new_monster(location);

	for (int i = 0; i < m_vector_of_strings.size(); i++)
	{
		for (int j = 0; j < m_vector_of_strings[i].size(); j++)
		{
			switch (m_vector_of_strings[i][j])
			{

			case player:
				location.row = i;
				location.col = j;
				playerLocation = location;

				
			case coin:
				location.row = i;
				location.col = j;
				new_coin.relocate(location);
				coins.push_back(new_coin);

				

			case enemy:
				location.row = i;
				location.col = j;
				new_monster.relocate(location);
				monsters.push_back(new_monster);
				
			}
		}
	}
}

// prints the board
void Board::print_board()
{
	for (int i = 0; i < m_vector_of_strings.size(); i++)
		std::cout << m_vector_of_strings[i] << std::endl;
}

void Board::print_board2()
{
	for (int i = 0; i < m_clean_vector_of_strings.size(); i++)
		std::cout << m_clean_vector_of_strings[i] << std::endl;
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

//returns which char there is an a specific location
char Board::get_char(Location& location) {
	return m_vector_of_strings[location.row][location.col];
}

char Board::get_char(int row, int col) 
{
	return m_vector_of_strings[row][col];
}

char Board::get_clean_board_char(int row, int col)
{
	return m_clean_vector_of_strings[row][col];
}

void Board::replace_char(Location &location)
{
	m_vector_of_strings[location.row][location.col] = m_clean_vector_of_strings[location.row][location.col];
}

void Board::delete_char(Location& location)
{
	m_vector_of_strings[location.row][location.col] = ' ';
}

void Board::add_char(Location& location, char sign)
{
	m_vector_of_strings[location.row][location.col] = sign;
}

void Board::clear_board()
{
	for (int i = 0; i < m_vector_of_strings.size(); i++)
	{
		m_vector_of_strings[i].clear();
		m_clean_vector_of_strings[i].clear();
	}

	m_vector_of_strings.clear();
	m_clean_vector_of_strings.clear();
}
