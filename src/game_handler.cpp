#include "game_handler.h"


Game_Handler::Game_Handler(Board& board)
	:m_board(board),
	 m_player(Location(0,0)) //default constructor
{
	init_player(board);
	// floor poll etc...
}

// runs the game
// main function
void Game_Handler::Run_game() {

	int key; //  right now it will be W,A,S,D key

	while (1) {
		//loads the level
		m_board.print_board ();
		

		print_player_location();

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

void Game_Handler::init_player(Board& board) {
	Location playerLocation = board.get_location_of_player();
	m_player = Player(playerLocation);
}

void Game_Handler::print_player_location()
{
	std::cout << std::endl << "(" << m_player.get_location().row << " , " << m_player.get_location().col << ")";
}

void Game_Handler::move_player(int key)
{
	Location current_location = m_player.get_location(); // lets us hold value, where the player stands

	// fills with space
	m_board.delete_char(current_location);

	//updates the location
	current_location.update_based_on_key(key);

	m_player.set_loctaion(current_location);
	
	m_board.add_char(current_location, '@');

}

	/*
	enum nextStep next = what_is_there_ehead();
	
switch(next)
	case Wall:
		// no move -> enemies move
	case Coin:
		// delete coin up score
	case Enemy:
		// down life reset position
	case Pole:
		//klimb pole -> enemies move
	case Ground:
		move_player(key);
		// move -> enemies
	case Ladder:
		// climb ladder -> enemies move
	case NoGround:
		// fall till ground
	default:
		//neet to thike

}


void Game_Handler::move_player(int key) {
		//ADD - get player location
		Location curr_loc = m_player.get_location();
		//ADD - update best on key
		curr_loc.update_based_on_key(key);

		m_player.set_loctaion(curr_loc);

}
*/
