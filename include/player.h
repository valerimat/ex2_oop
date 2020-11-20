#pragma once
const int NUMBER_OF_LIVES = 3;
#include "Score.h"
#include "Lives.h"
#include "Location.h"


class Player {

public:
	Player (Location location);
	Player();

	Location get_location();
	
	void set_loctaion(Location& new_location);
	
	void increse_score(int value);
	void decrese_live();
	Score get_score();
	Lives get_lives();
	void reset(Location& starting_location);
	void set_lives(int lives);
	void set_score(int score);
	
private:

	
	Score m_player_score;
	Lives m_player_lives;
	Location m_player_loctaion;
	
};