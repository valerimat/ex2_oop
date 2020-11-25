#include <iostream>
#include <vector>
#include "Board.h"
#include "player.h"
#include "io.h"
#include "Location.h"
#include "Coin.h"
#include "Monster.h"
#include "AlphaStar.h"
#include "macros.h"

enum nextStep {
	Wall,
	Coin,
	Enemy,
	Pole,
	Ground,
	NoGround,
	Ladder
};



class Game_Handler {
public:
	Game_Handler(Board& board);

	Board m_board;

	enum nextStep what_is_there_ahead(int key);

	//private ??
	void Run_game();
	Player m_player;
	bool move_player(int key);
	void print_player_location();
	void move_enemies();
	//debug functions
	void delete_coin_from_vector(Location location);
	bool no_coins();
	void init_new_level();
	void random_move(Monster& monster, int);
	char there_is_a_monster(Location& location);
	void move_based_on_dirrection(bool x, int direct, Monster& monster);
	void move_based_on_dirrection(int dirrection, Monster& monster);
	void die();
	std::vector<Monster> m_monsters;
	std::vector<Coins> m_coins;

private:
	void you_won();
	void load_next_level();

	/*
	
	

	
	
	//vector Enemies m_enemy;
	//vector coins
	//????? why we need entety for floor poll and lacder
	//vectro floor
	//vector poll
	//vector ladder
	*/
};