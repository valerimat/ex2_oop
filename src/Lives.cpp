//======include header======
#include "Lives.h"

//===============C-TORS===============
Lives::Lives(int lives) : m_number_of_live(lives) {};
//----------------------------------------------------------------------------

//===============Helpers===============

// decreases the lives
void Lives::decrese() { m_number_of_live--; }
//----------------------------------------------------------------------------

// get function which returns the lives
int Lives::get_lives() { return m_number_of_live; };
//----------------------------------------------------------------------------