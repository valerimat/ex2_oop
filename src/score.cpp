
#include "Score.h"

Score::Score(int score) : score(score) {};

void Score::increase(int value) { score += value; }

int Score::get_score() { return m_score; };