//======include header======
#include "Monster.h"

// c-tor
Monster::Monster(Location& location) 
	:m_location(location), m_smartnes(rand()%10) ,curr_smartnes(0)
{}; 
//----------------------------------------------------------------------------
	
// decreases the monster's IQ inorder to make the game much easier
void Monster::dec_smartnes()
{
	curr_smartnes--;
};
//----------------------------------------------------------------------------

// reset the smartness
void Monster::reset_smartnes()
{
	curr_smartnes = m_smartnes;
};
//----------------------------------------------------------------------------

// changes monsters location
void Monster::relocate(Location &location)
{
	m_location = location;
};
//----------------------------------------------------------------------------

//===============Getters===============

// gets us how smart the monster set to
int Monster::get_smartnes()
{
	return curr_smartnes;
};
//----------------------------------------------------------------------------

// gets us monster location
Location Monster::get_location()
{
	return m_location;
};
//----------------------------------------------------------------------------

// get monster's char
char Monster::get_deleted_it()
{
	return m_deleted_it;
};
//----------------------------------------------------------------------------

//===============Setters===============

// sets the monster with char
void Monster::set_deleted_it(char c)
{
	m_deleted_it = c;
};
//----------------------------------------------------------------------------

