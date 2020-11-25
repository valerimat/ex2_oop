#include "player.h"



Player::Player(Location loctaion)
    :m_player_loctaion(loctaion),
     m_player_score(Score(0)),
     m_player_lives(Lives(3))
{ };

//default constructor
Player::Player() 
    :m_player_loctaion(Location(0, 0)),
    m_player_score(Score(0)),
    m_player_lives(Lives(3))
    {  };

Location Player::get_location() {
    return m_player_loctaion;
};

void Player::set_loctaion(Location& new_location) {
    m_player_loctaion = new_location;
};


void Player::increse_score(int level) {
    m_player_score.increase(level);
};

void Player::increse_score_end_level(int level) {
    m_player_score.level_end(level);
};

void Player::decrese_live() {
    m_player_lives.decrese();
};


//============================= Getters
int Player::get_score() {
    return m_player_score.get_score();
};


int Player::get_lives() {
    return m_player_lives.get_lives();
};



void Player::reset(Location &starting_location) {
    set_loctaion(starting_location);
    set_lives(NUMBER_OF_LIVES);
    set_score(0);
};


//============================= Setters



void Player::set_lives(int lives) {
    m_player_lives = Lives(lives);
}

void Player::set_score(int score) {
    Score newScore = Score(score);
    m_player_score = Score(score);

}
