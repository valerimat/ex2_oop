//======include header======
#include "Game_handler.h"
#include "io.h"

// c-tor
Game_Handler::Game_Handler(Board& board) :m_board(board)
{
	init_new_level();
}
//----------------------------------------------------------------------------
// runs the game - main function
void Game_Handler::Run_game()
{
	bool end = false;
	int key;
	
	while (1) 
	{
		// prints the level bar
		std::cout << "           LEVEL - " << m_board.get_level() << std::endl;

		//loads the level
		m_board.print_board();

		std::cout << "     lives - " << m_player.get_lives() <<
					 ", score - " << m_player.get_score() << std::endl;

		key = get_proper_key();

		if (key == KB_ESC)
		{
			system("CLS");
			you_left();		
		}

		//if wasnt a valid move		
		if (!move_player(key)) {
			system("CLS");
			continue;
		}
			

		//checks if all the coins were collected in the level
		end = no_coins();
		if (end) {

			load_next_level();
			continue;
		}		
		move_enemies(); // move enemies

		system("CLS"); // clears the screen
	}
}
//----------------------------------------------------------------------------

// main function where the player moves according to the all ifs
bool Game_Handler::move_player(int key)
{	
	enum nextStep next = what_is_there_ahead(key);
	Location current_location = m_player.get_location(); // lets us hold the axis, where the player stands

	if (next != NoGo)
	{
		if (m_board.get_char(current_location.row + 1, current_location.col) != ' ' ||
			m_board.get_clean_board_char(current_location.row, current_location.col) == '-')
		{
			if (m_board.return_char_from_default(m_player.get_location()) == 'H')
				if (key == KB_UP) {
					m_board.replace_char(current_location); // inserts the original char back to place
					current_location.update_based_on_key(key); // we get the new location based on the key
					m_player.set_loctaion(current_location);
					m_board.add_char(current_location, '@');
					return true;
				}

			switch (next)
			{
			case Wall: // #
				m_board.add_char(current_location, '@');
				return false;

				break;

			case Ladder: // H
				m_board.replace_char(current_location);		// inserts the original char back to place
				current_location.update_based_on_key(key);  // we get the new location based on the key
				m_player.set_loctaion(current_location);	// sets the new location in the vector
				m_board.add_char(current_location, 'S');	// inserts the player in the tile
				break;

			case Pole: // - 
				if (key == KB_UP)
				{
					m_board.add_char(current_location, '@'); //cannot get above the pole
				}
				else
				{
					m_board.replace_char(current_location);		// inserts the original char back to place
					current_location.update_based_on_key(key);  // we get the new location based on the key
					m_player.set_loctaion(current_location);	// sets the new location in the vector
					m_board.add_char(current_location, '@');	// inserts the player in the tile
				}
				break;

			case Coin:
				m_board.replace_char(current_location);		// inserts the original char back to place
				current_location.update_based_on_key(key);  // we get the new location based on the key
				m_player.set_loctaion(current_location);	// sets the new location in the vector
				m_board.add_char(current_location, '@');	// inserts the player in the tile
				//update score
				m_player.increse_score(m_board.get_level());
				//delete from vector
				delete_coin_from_vector(m_player.get_location());
				break;

			case Enemy: // %
				die();

			default: // Ground
				if (key == KB_UP)
				{
					m_board.add_char(current_location, '@');
				}
				else
				{
					m_board.replace_char(current_location);		// inserts the original char back to place
					current_location.update_based_on_key(key);  // we get the new location based on the key
					m_player.set_loctaion(current_location);	// sets the new location in the vector
					m_board.add_char(current_location, '@');	// inserts the player in the tile
				}
				break;
			}
		}
		else

		{
			// free fall - nothing stops the player till he reaches ground beneath

			while (m_board.get_char(current_location.row + 1, current_location.col) == ' ')
			{
				m_board.replace_char(current_location);		// inserts the original char back to place
				current_location.update_based_on_key(KB_DOWN);  // 115 is down in the KB
				m_player.set_loctaion(current_location);	// sets the new location in the vector
				m_board.add_char(current_location, '@');	// inserts the player in the tile
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

// we get whats ahead of the player using enum to make it more clear
enum nextStep Game_Handler::what_is_there_ahead(int key)
{
	Location current_location = m_player.get_location();
	char current_letter;

	if (key == KB_UP) // up
		current_location.row--;
	if (key == KB_DOWN) // down
		current_location.row++;
	if (key == KB_LEFT) // left
		current_location.col--;
	if (key == KB_RIGHT) // right
		current_location.col++;

	if (current_location.row == -1 || current_location.row == m_board.get_height() -1 ||
		current_location.col == -1 || current_location.col == m_board.get_width() - 1)
		return NoGo;

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
//----------------------------------------------------------------------------

// in case the player died (= 0 lives) 
void Game_Handler::die()
{
		
	if (m_player.get_lives()-1 == 0)
	{
		system("CLS");
		std::cout << "###########################################################		\n"
				  << "                     YOU HAVE DIED !!!							\n"
				  << "                        Try Again									\n"
				  << "                    Your Score is: " << m_player.get_score() << " \n"
				  << "###########################################################		\n";
		exit(EXIT_SUCCESS);
	}
	else
	{
		m_board.relload_level();
		//loads same level
		m_player.decrese_live();

		system("CLS");

		init_new_level();

		Run_game();
	}
}
//----------------------------------------------------------------------------

void Game_Handler::move_enemies()
{

	int how_many_enemies = m_monsters.size();
	
	//if there are no enemies
	if (how_many_enemies == 0)
		return;

	int index = 0;

	Location player_location = m_player.get_location();
			

	for (index; index < how_many_enemies; index++)
	{
		Location monster_location = m_monsters[index].get_location();

			if (m_monsters[index].get_smartnes() == 0)
			{
				//calcl path
				m_monsters[index].set_path(CalculatePath(monster_location, player_location, m_board));
				//reset smartnes
				m_monsters[index].reset_smartnes();
			}
			else
			{
				m_monsters[index].dec_smartnes();
			}
			
			int length_of_path = m_monsters[index].get_path_size();					

			if(length_of_path == 0){
				move_based_on_dirrection(NONE, m_monsters[index]);
				continue;
			}
			
			if (rand() % 8 == 1) {
				random_move(m_monsters[index], m_monsters[index].get_next_path());
				m_monsters[index].remove_first_in_path();
				continue;
			}
				
			move_based_on_dirrection(m_monsters[index].get_next_path(), m_monsters[index]);
			m_monsters[index].remove_first_in_path();

		}

};
//----------------------------------------------------------------------------

void Game_Handler::random_move(Monster& monster, int next_move) {
	
	Location monster_l = monster.get_location();

	if(next_move == UP)
		if(m_board.get_char(monster_l.row +1, monster_l.col) != '#')
			move_based_on_dirrection(DOWN, monster);
		else 
			move_based_on_dirrection(rand()%2, monster);

	else if (next_move == LEFT) {
		if (m_board.get_char(monster_l.row + 1, monster_l.col) == 'H') {
			if (rand() % 1 == 1)
				move_based_on_dirrection(UP, monster);
			else
				move_based_on_dirrection(RIGHT, monster);
		}
		else {
			if (m_board.get_char(monster_l.row, monster_l.col - 1) != '#')
				move_based_on_dirrection(RIGHT, monster);
			else
				move_based_on_dirrection(LEFT, monster);
		}
	}

	else if (next_move == RIGHT) {
		if (m_board.get_char(monster_l.row + 1, monster_l.col) == 'H') {
			if (rand() % 1 == 1)
				move_based_on_dirrection(UP, monster);
			else
				move_based_on_dirrection(LEFT, monster);
		}
		else {
			if (m_board.get_char(monster_l.row, monster_l.col + 1) != '#')
				move_based_on_dirrection(LEFT, monster);
			else
				move_based_on_dirrection(RIGHT, monster);
		}
	}
	else {
		move_based_on_dirrection(next_move, monster);
	}
	
}



void Game_Handler::move_based_on_dirrection(int dirrection, Monster& monster)
{
	//we dont need to move

	//returning char we previously deleted
	m_board.add_char(monster.get_location(), monster.get_deleted_it());

	//if x_axis
	bool x_axis = true;

	//adding more stupidity
	
	switch ((enum Moves)dirrection)
	{
	case UP:
		move_based_on_dirrection(!x_axis, -1, monster);
		break;

	case DOWN:
		move_based_on_dirrection(!x_axis, 1, monster);
		break;

	case RIGHT:
		move_based_on_dirrection(x_axis, 1, monster);
		break;
	case LEFT:
		move_based_on_dirrection(x_axis, -1, monster);
		break;
	case NONE:
		move_based_on_dirrection(x_axis, 0, monster);
	}
}
//----------------------------------------------------------------------------

void Game_Handler::move_based_on_dirrection(bool x_axis, int direct, Monster & monster)
{
	
	Location new_location(0, 0);

	if (x_axis)
		new_location = Location(monster.get_location().row, monster.get_location().col + direct);
	else
		new_location = Location(monster.get_location().row + direct, monster.get_location().col );
	
char check_if_there_is_monster = there_is_a_monster(new_location);
	
	if(check_if_there_is_monster!= '\0')
		monster.set_deleted_it(check_if_there_is_monster);
	else
		monster.set_deleted_it(m_board.get_char(new_location));

	if (monster.get_deleted_it() == '@')
		die();

	monster.relocate(new_location);
	m_board.add_char(new_location, '%');
}
//----------------------------------------------------------------------------

// deletes the coin from the vector when the player steps on it
void Game_Handler::delete_coin_from_vector(Location  location)
{
	for (size_t index = 0; index < m_coins.size(); index++)
	{
		if (m_coins[index].get_location() == location)
		{
			m_coins.erase(m_coins.begin() + index);
		}
	}
}
//----------------------------------------------------------------------------



char Game_Handler::there_is_a_monster(Location & location) {
	if (m_board.get_char(location) == '%') {
		int index = 0;

		while (m_monsters[index].get_location() != location)
			index++;

		return m_monsters[index].get_deleted_it();
	}

	return '\0';
	
}


// loads the next level, if there are no more levels then the player won
void Game_Handler::load_next_level()
{
	system("CLS");

	if (m_board.no_more_levels())
		you_won();

	m_player.increse_score_end_level(m_board.get_level());

	m_board.load_next_level();
	
	init_new_level();
}
//----------------------------------------------------------------------------

// checks if there are coins left 
bool Game_Handler::no_coins()
{
	if (m_coins.size() == 0)
		return true;
	
	return false;
}
//----------------------------------------------------------------------------

// initializes all the info about the level
void Game_Handler::init_new_level()
{
	Location player_location(0, 0);
	m_monsters.clear();

	m_coins.clear();

	m_board.get_locations(m_monsters, m_coins, player_location);

	m_player.set_loctaion(player_location);
}
//----------------------------------------------------------------------------

// prints the following text below if the player won
void Game_Handler::you_won() 
{
	std::cout << "###########################################################     \n"
			  << "                     YOU HAVE WON!							  \n"
			  << "                   Thanks for playing							  \n"
			  << "                  Your score is: " << m_player.get_score()  << "\n"
			  << "###########################################################     \n";

	exit(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------

// prints the following text below if the player won
void Game_Handler::you_left()
{
	std::cout << "###########################################################     \n"
			  << "           you have left the game unfinished			          \n"
			  << "                   Thanks for trying						      \n"
			  << "                  Your score is: " << m_player.get_score()  << "\n"
			  << "###########################################################     \n";

	exit(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------

// get arrow key from the user unsless ESC was typed
int Game_Handler::get_proper_key()
{
	int key = Keyboard::getch();
	
	while (key != 224)
	{
		if (key == 27)
			return key; // ESC
		key = Keyboard::getch();
	}

	return Keyboard::getch();
}