#include "Score.h"

Score::Score(int score) : m_score(score) {};

void Score::increase(int value) { m_score += value; }

int Score::get_score() { return m_score; };