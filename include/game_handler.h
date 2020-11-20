#include "Board.h"
#include "player.h"
#include "io.h"
#include <iostream>	
#include "Location.h"
#include <vector>
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

	//private ??
	void Run_game();
	Player m_player;
	void init_player(Board&);
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