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
  
	int score = 0;

	while (1)
	{
		std::cout << "         LEVEL - X\n";
		//loads the level
		m_board.print_board ();

		std::cout << "     health - X , score - Y\n";

		//fix to work with W,A,S,D
		int key = Keyboard::getch();

		// add key is valid		
		movement(key);

		// clears the screen

		// move enemies
		move_enemies();

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
		case Coin: // *
			// add it later
		case Enemy: // %
			// add it later
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

void Game_Handler::print_player_location()
{
	std::cout << std::endl << "( " << m_player.get_location().row <<
						     " , " << m_player.get_location().col << " )";
}


void Game_Handler::move_enemies() {
	int how_many_enemies = m_monsters.size();
	int index = 0;
	Location player_location = m_player.get_location();

	if (how_many_enemies != 0) {
		for (index; index < how_many_enemies; index++) {
			Location monster_location = m_monsters[index].get_location();
			if (m_board.get_char(monster_location.row + 1, monster_location.col) == ' ' && m_monsters[index].get_deleted_it() != '-' ) {
				//if nothing bellow and we are not on a pole
				move_based_on_dirrection(DOWN, m_monsters[index]);
				continue;
			}
			if (m_monsters[index].get_smartnes() == 0) {
				//calcl path
				m_monsters[index].path = CalculatePath(monster_location, player_location, m_board);
				//reset smartnes
				m_monsters[index].reset_smartnes();
			}
			m_monsters[index].dec_smartnes();

			//can implement better with
			int length_of_path = m_monsters[index].path.size();
			move_based_on_dirrection(m_monsters[index].path[0] , m_monsters[index]);
			m_monsters[index].path.erase(m_monsters[index].path.begin());

		}

	}
};






void Game_Handler::move_based_on_dirrection(int dirrection, Monster& monster) {

	//we dont need to move
	if (dirrection == NONE)
		return;


	m_board.add_char(monster.get_location(), monster.get_deleted_it());

	Location monster_location = monster.get_location();
	Location new_location(0,0);


	switch ((enum Moves)dirrection)
	{

	case UP:
		new_location = Location(monster_location.row - 1, monster_location.col);
		monster.set_deleted_it(m_board.get_char(new_location));
		monster.relocate(new_location);
		m_board.add_char(new_location, '%');
		break;

	case DOWN:
		new_location = Location(monster_location.row + 1, monster_location.col);
		monster.set_deleted_it(m_board.get_char(new_location));
		monster.relocate(new_location);
		m_board.add_char(new_location, '%');
		break;

	case RIGHT:
		new_location = Location(monster_location.row, monster_location.col+1);
		monster.set_deleted_it(m_board.get_char(new_location));
		monster.relocate(new_location);
		m_board.add_char(new_location, '%');
		break;

	case LEFT:
		new_location = Location(monster_location.row, monster_location.col-1);
		monster.set_deleted_it(m_board.get_char(new_location));
		monster.relocate(new_location);
		m_board.add_char(new_location, '%');
		break;

	}

}