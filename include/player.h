#pragma once
#include "macros.h"
#include "Score.h"
#include "Lives.h"
#include "Location.h"


class Player {

public:
	
	//----------------------------C-TORS
	Player (Location location);
	Player();
	Location get_location();
	
	void set_loctaion(Location& new_location);
	
	void increse_score(int value);
	void decrese_live();
	int get_score();
	int get_lives();
	void reset(Location& starting_location);
	void set_lives(int lives);
	void set_score(int score);
	void increse_score_end_level(int level);
	
private:

	
	Score m_player_score;
	Lives m_player_lives;
	Location m_player_loctaion;
	
};