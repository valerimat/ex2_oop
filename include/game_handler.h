#include <iostream>
#include <vector>
#include "Board.h"
#include "player.h"
#include "io.h"
#include "Location.h"
#include "Coin.h"
#include "Monster.h"

enum nextStep {
	Wall,
	Coin,
	Enemy,
	Pole,
	Ground,
	NoGround,
	Ladder
};

enum key {
	UP,
	DOWN,
	LEFT,
	RIGHT
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

	//TESTING

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