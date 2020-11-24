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
	void movement(int key);
	enum nextStep what_is_there_ahead(int key);

	//private ??
	void Run_game();
	Player m_player;
	void move_player(int key);
	void print_player_location();
	void move_enemies();
	//debug functions
	void delete_coin_from_vector(Location location);
	bool no_coins();
	void init_new_level();

	int m_level;

	void move_based_on_dirrection(int dirrection, Monster& monster);

	std::vector<Monster> m_monsters;
	std::vector<Coins> m_coins;



	/*
	
	

	
	
	//vector Enemies m_enemy;
	//vector coins
	//????? why we need entety for floor poll and lacder
	//vectro floor
	//vector poll
	//vector ladder
	*/
};