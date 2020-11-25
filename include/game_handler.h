#pragma once

//======include section======
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

enum nextStep
{
	Wall,
	Coin,
	Enemy,
	Pole,
	Ground,
	NoGround,
	Ladder
};

class Game_Handler
{
public:
	// c-tor
	Game_Handler(Board& board);

	// getters
	int get_proper_key();


	// setters

	// move
	void move_based_on_dirrection(bool x, int direct, Monster& monster);
	void move_based_on_dirrection(int dirrection, Monster& monster);
	bool move_player(int key);
	void move_enemies();
void random_move(Monster& monster, int);

	//misc
	void Run_game();
	enum nextStep what_is_there_ahead(int key);
	void delete_coin_from_vector(Location location);
	char there_is_a_monster(Location& location);

	//end level/game
	void init_new_level();
	void you_left();
	void die();
	bool no_coins();	

private:
	Board  m_board;
	Player m_player;
	std::vector<Monster> m_monsters;
	std::vector<Coins>   m_coins;
	void you_won();
	void load_next_level();
};