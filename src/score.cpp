#include "Score.h"

Score::Score(int score) : m_score(score) {};

void Score::increase(int level) { m_score += 2 * level; };

void Score::level_end(int level) { m_score += 50 * level; };

int Score::get_score() { return m_score; };