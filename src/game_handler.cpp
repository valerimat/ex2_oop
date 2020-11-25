#include "Game_handler.h"


Game_Handler::Game_Handler(Board& board)
	:m_board(board)
{
	init_new_level();
}


// runs the game
// main function
void Game_Handler::Run_game()
{

	bool end = false;

	int key; //  right now it will be W,A,S,D key
  
	
	while (1)
	{
		std::cout << "         LEVEL -  " << m_board.get_level() << std::endl;
		//loads the level
		m_board.print_board();

	
		std::cout << "     health - "<<  m_player.get_lives()  <<" , score - " << m_player.get_score();

		//fix to work with W,A,S,D
		int key = Keyboard::getch();

		// add key is valid		
		movement(key);

		//check if we collected all coins
		end = no_coins();
		if (end) {

			load_next_level();
	
			continue;
		}
		

		// move enemies
		move_enemies();

		// clears the screen

		system("CLS");


	}
}

void Game_Handler::movement(int key) {
	move_player(key); 
}

void Game_Handler::move_player(int key)
{	
	enum nextStep next = what_is_there_ahead(key);
	Location current_location = m_player.get_location(); // lets us hold the axis, where the player stands

	if (m_board.get_char(current_location.row + 1, current_location.col) != ' ' ||
		m_board.get_clean_board_char(current_location.row, current_location.col) == '-')
	{
		switch (next)
		{
		case Wall: // #
			// no move, but enemies move
			m_board.add_char(current_location, '@');
			// enemy moves;
			break;
		case Ladder: // H
			m_board.replace_char(current_location); // inserts the original char back to place
			current_location.update_based_on_key(key); // we get the new location based on the key
			m_player.set_loctaion(current_location);
			m_board.add_char(current_location, '@');
			break;

		case Pole: // - 
			if (key == 119)
			{
				m_board.add_char(current_location, '@');
				// enemy moves;
			}
			else
			{
				m_board.replace_char(current_location); // inserts the original char back to place
				current_location.update_based_on_key(key); // we get the new location based on the key
				m_player.set_loctaion(current_location);
				m_board.add_char(current_location, '@');
			}
			break;
			// enemy moves;
		case Coin:
			m_board.replace_char(current_location); // inserts the original char back to place
			current_location.update_based_on_key(key); // we get the new location based on the key
			m_player.set_loctaion(current_location);
			m_board.add_char(current_location, '@');
			//update score
			m_player.increse_score(m_board.get_level());
			//delete from vector
			delete_coin_from_vector(m_player.get_location());
			break;

		case Enemy: // %
			die();
		default: // Ground
			if (key == 119)
			{
				m_board.add_char(current_location, '@');
				// enemy moves;
			}
			else
			{
				m_board.replace_char(current_location); // inserts the original char back to place
				current_location.update_based_on_key(key); // we get the new location based on the key
				m_player.set_loctaion(current_location);
				m_board.add_char(current_location, '@');
			}
			break;
		}
	}
	else
	{
		// free fall
		while (m_board.get_char(current_location.row + 1, current_location.col) == ' ')
		{
			m_board.replace_char(current_location); // inserts the original char back to place
			current_location.update_based_on_key(115); // 115 is down in the KB
			m_player.set_loctaion(current_location);
			m_board.add_char(current_location, '@');
		}
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


void Game_Handler::die() {
		
	if (m_player.get_lives()-1 == 0) {
		system("CLS");
		std::cout << "              YOU HAVE DIED !!!\n" << "              Try Again\n"
			<< "              Your Score  : " << m_player.get_score();
		exit(EXIT_SUCCESS);
	}
	else {
		m_board.relload_level();
		//loads same level
		m_player.decrese_live();

		system("CLS");

		init_new_level();

		Run_game();
	}
}

void Game_Handler::move_enemies() {

	int how_many_enemies = m_monsters.size();
	
	//if no enemies
	if (how_many_enemies == 0)
		return;

	int index = 0;

	Location player_location = m_player.get_location();
			

	for (index; index < how_many_enemies; index++) {

	

		Location monster_location = m_monsters[index].get_location();

			if (m_monsters[index].get_smartnes() == 0) {
				//calcl path
				m_monsters[index].path = CalculatePath(monster_location, player_location, m_board);
				//reset smartnes
				m_monsters[index].reset_smartnes();
			}
			else {
				m_monsters[index].dec_smartnes();

			}
			
	
			int length_of_path = m_monsters[index].path.size();

					

			if(length_of_path == 0){
				move_based_on_dirrection(NONE, m_monsters[index]);
				continue;
			
			}
				


			move_based_on_dirrection(m_monsters[index].path[0] , m_monsters[index]);
			m_monsters[index].path.erase(m_monsters[index].path.begin());

		}

	
};




void Game_Handler::move_based_on_dirrection(int dirrection, Monster& monster) {

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



void Game_Handler::move_based_on_dirrection(bool x_axis, int direct, Monster & monster) {
	
	Location new_location(0, 0);

;	if (x_axis) {
		new_location = Location(monster.get_location().row, monster.get_location().col + direct);
	}
	else {
		new_location = Location(monster.get_location().row + direct, monster.get_location().col );
	}
	
	monster.set_deleted_it(m_board.get_char(new_location));

	if (monster.get_deleted_it() == '@')
		die();

	monster.relocate(new_location);
	m_board.add_char(new_location, '%');
}


void Game_Handler::delete_coin_from_vector(Location  location) {

	for (size_t index = 0; index < m_coins.size(); index++) {

		if (m_coins[index].get_location() == location) {
			m_coins.erase(m_coins.begin() + index);
		}
	}
}


void Game_Handler::load_next_level() {
	system("CLS");
	m_player.increse_score_end_level(m_board.get_level());

	if (m_board.no_more_levels())
		you_won();

	m_board.load_next_level();

	init_new_level();
}



bool Game_Handler::no_coins(){
	if (m_coins.size() == 0)
		return true;
	
return false;

}

void Game_Handler::init_new_level() {
	Location player_location(0, 0);
	m_monsters.clear();

	m_coins.clear();

	m_board.get_locations(m_monsters, m_coins, player_location);

	m_player.set_loctaion(player_location);

}


void Game_Handler::you_won() {
	std::cout << "           YOU HAVE WON" << std::endl;
	std::cout << "           Thanks for playing" << std::endl;
	std::cout << "           Your score is: " << m_player.get_score()<<std::endl;

	exit(EXIT_SUCCESS);
}