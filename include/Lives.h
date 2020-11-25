#pragma once

// Lives struct 
struct Lives
{
public:
	// c-tor
	Lives(int lives);
	// d-tor
	~Lives() = default;

	//functions
	int get_lives();
	void decrese();

private:
	int m_number_of_live;
};