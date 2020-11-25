//======include header======
#include "player.h"

// c_tor
Player::Player(Location loctaion)
    :m_player_loctaion(loctaion),
     m_player_score(Score(0)),
     m_player_lives(Lives(3))
{};
//----------------------------------------------------------------------------

//default constructor
Player::Player() 
    :m_player_loctaion(Location(0, 0)),
     m_player_score(Score(0)),
     m_player_lives(Lives(3))
{};
//----------------------------------------------------------------------------

// increases the score of the plauer
void Player::increse_score(int level)
{
    m_player_score.increase(level);
};
//----------------------------------------------------------------------------

// increases the score as the level finished
void Player::increse_score_end_level(int level)
{
    m_player_score.level_end(level);
};
//----------------------------------------------------------------------------

// decreases the lives of the player
void Player::decrese_live()
{
    m_player_lives.decrese();
};
//----------------------------------------------------------------------------

// resets player location
void Player::reset(Location &starting_location)
{
    set_loctaion(starting_location);
    set_lives(NUMBER_OF_LIVES);
    set_score(0);
};
//----------------------------------------------------------------------------

//===============Getters===============

// gets us the score
int Player::get_score()
{
    return m_player_score.get_score();
};
//----------------------------------------------------------------------------

// gets us the lives of the player
int Player::get_lives()
{
    return m_player_lives.get_lives();
};
//----------------------------------------------------------------------------

// gets us the location of the player
Location Player::get_location()
{
    return m_player_loctaion;
};
//----------------------------------------------------------------------------

//===============Setters===============

// sets the lives according to the input
void Player::set_lives(int lives)
{
    m_player_lives = Lives(lives);
}
//----------------------------------------------------------------------------

// sets the score
void Player::set_score(int score)
{
    Score newScore = Score(score);
    m_player_score = Score(score);
}
//----------------------------------------------------------------------------

// sets the player location
void Player::set_loctaion(Location &new_location)
{
    m_player_loctaion = new_location;
};
//----------------------------------------------------------------------------
