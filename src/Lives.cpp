
#include "Lives.h"

Lives::Lives(int lives) : m_number_of_live(lives) {};

void Lives::decrese() { m_number_of_live--; }

int Lives::get_lives() { return m_number_of_live; };