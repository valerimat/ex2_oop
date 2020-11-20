#pragma once



class Score {

public:
	Score(int score);
	~Score() = default;
	void increase(int value);
	int get_score();

private:
	int m_score;

};