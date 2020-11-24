#pragma once



class Score {

public:
	Score(int score);
	~Score() = default;
	void increase(int level);
	int get_score();
	void level_end(int level);
private:
	int m_score;

};