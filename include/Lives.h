



struct Lives {
		
	Lives(int lives);
	~Lives() = default;

	int get_lives();
	void decrese();

	private:
		int m_number_of_live;

};