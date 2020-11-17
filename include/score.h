#pragma once



class Score {

	Score(int score);
 ~Score() = default;
	void increase(int value);
	int get_score();

private:
	int m_score;

};