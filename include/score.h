#pragma once

class Score
{
public:
	// c-tor 
	Score(int score);
	// d-tor
	~Score() = default;

	// get function
	int get_score();

	// misc
	void increase(int level);
	void level_end(int level);

private:
	int m_score;
};