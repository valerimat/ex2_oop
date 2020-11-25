#pragma once

#include "Score.h"
#include "Lives.h"
#include "Location.h"
#include "macros.h"

class Player {

public:
	// c-tors
	Player (Location location);
	Player();

	// getters
	int get_score();
	int get_lives();
	Location get_location();

	// setters
	void set_loctaion(Location& new_location);
	void set_lives(int lives);
	void set_score(int score);

	// misc
	void increse_score(int value);
	void decrese_live();
	void reset(Location& starting_location);
	void increse_score_end_level(int level);
	
private:
	Score m_player_score;
	Lives m_player_lives;
	Location m_player_loctaion;
	
};