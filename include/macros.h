#pragma once

//======const section======
const int NUMBER_OF_LIVES = 3;
const int BASE_SCORE = 0;

//=======enum section=======
enum Moves {
	UP,
	LEFT,
	RIGHT,
	DOWN,
	NONE
};

enum nextStep
{
	Wall,
	Coin,
	Enemy,
	Pole,
	Ground,
	NoGround,
	Ladder,
	NoGo
};