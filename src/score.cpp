//======include header======
#include "Score.h"

//===============C_tors===============
Score::Score(int score) : m_score(score) {};
//----------------------------------------------------------------------------

//===============Helpers===============
// each coin gains (2 * level) points to the score
void Score::increase(int level) { m_score += 2 * level; };
//----------------------------------------------------------------------------

// each completed level gains (50 * level) points to the score
void Score::level_end(int level) { m_score += 50 * level; };
//----------------------------------------------------------------------------

// gets us the current score
int Score::get_score() { return m_score; };
//----------------------------------------------------------------------------