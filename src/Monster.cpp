#include "Monster.h"



Monster::Monster(Location& location) : m_location(location), m_smartnes(rand()%4) ,curr_smartnes(0)
{}; 
	

void Monster::dec_smartnes() {
	curr_smartnes--;
};

void Monster::reset_smartnes() {
	curr_smartnes = m_smartnes;
};

int Monster::get_smartnes() {
	return curr_smartnes;
};
Location Monster::get_location() {
	return m_location;
};

char Monster::get_deleted_it() {
	return m_deleted_it;
};
void Monster::set_deleted_it(char c) {
	m_deleted_it = c;
};
void Monster::relocate(Location& location)
{
	m_location = location;
};