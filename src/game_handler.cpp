#include "Game_handler.h"


Game_Handler::Game_Handler(Board& board)
	:m_board(board)
{
	Location player_location(0, 0);

	board.get_locations(m_monsters, m_coins, player_location);

	m_player.set_loctaion(player_location);

}


// runs the game
// main function
void Game_Handler::Run_game()
{

	int key; //  right now it will be W,A,S,D key

	while (1)
	{
		//loads the level
		m_board.print_board ();
		
		//fix to work with W,A,S,D
		int key = Keyboard::getch();

		// add key is valid		
		movement(key);

		// clears the screen
		system("CLS");

		//if player dead => exit

		//if  collected all coins => next level

	}
}

void Game_Handler::movement(int key) {
	move_player(key); 
}

void Game_Handler::move_player(int key)
{
	Location current_location = m_player.get_location(); // lets us hold the axis, where the player stands
	enum nextStep next = what_is_there_ahead(key);

	switch (next)
	{
		case Wall: // #
			// no move, but enemies move
			m_board.add_char(current_location, '@');
			// enemy moves;
			break;
		case Ladder: // H
			if(key == 119 || key == 115)
				m_board.add_char(current_location, 'H'); // needs to be fixed later
			else
				m_board.delete_char(current_location); // needs to be fixed later
			current_location.update_based_on_key(key);
			m_player.set_loctaion(current_location);
			m_board.add_char(current_location, '@');
			break;
				
		case Pole: // - 
			if (key == 97 || key == 100)
				m_board.add_char(current_location, '-'); // needs to be fixed later
			else
				m_board.delete_char(current_location); // needs to be fixed later
			m_board.delete_char(current_location); // needs to be fixed later
			current_location.update_based_on_key(key);
			m_player.set_loctaion(current_location);
			m_board.add_char(current_location, '@');
			break;
			// enemy moves;
		case Coin: // *
			// add it later
		case Enemy: // %
			// add it later
		case NoGround: // Hell
			m_board.delete_char(current_location); // needs to be fixed later
			current_location.update_based_on_key(115); // 115 is down in the KB
			m_player.set_loctaion(current_location);
			m_board.add_char(current_location, '@');
			break;
		default: // Ground - #
			m_board.delete_char(current_location); // needs to be fixed later
			if (key == 119)
			{
				m_board.add_char(current_location, '@');
			// enemy moves;
			}
			else
			{
				current_location.update_based_on_key(key); // 115 is down in the KB
				m_player.set_loctaion(current_location);
				m_board.add_char(current_location, '@');
			}
			break;
	}
}

enum nextStep Game_Handler::what_is_there_ahead(int key)
{
	enum nextStep situatuon;
	Location current_location = m_player.get_location();
	char current_letter;

	if (key == 119) // up
		current_location.row--;
	if (key == 115) // down
		current_location.row++;
	if (key == 97) // left
		current_location.col--;
	if (key == 100) // right
		current_location.col++;

	current_letter = m_board.get_char(current_location);

	if (current_letter == '#') 
		return Wall;
	if (current_letter == 'H')
		return Ladder;
	if (current_letter == '-')
		return Pole;
	if (current_letter == '*')
		return Coin;
	if (current_letter == '%')
		return Enemy;

	current_location.row++;

	current_letter = m_board.get_char(current_location);

	if (current_letter == ' ')
		return NoGround;

	return Ground;
}

void Game_Handler::print_player_location()
{
	std::cout << std::endl << "( " << m_player.get_location().row <<
						     " , " << m_player.get_location().col << " )";
}

