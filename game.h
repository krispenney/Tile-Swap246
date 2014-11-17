#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"

class Game {
	int level;
	static int score;
	int moves;
	Board * theBoard;
public:
	void hint();
	void levelUp();
	void levelDown();
	void scramble();
	void restart();
	static void increaseScore(int x);
	bool levelWon();


	friend std::ostream &operator<<(std::ostream &out, const Game &g);

};

#endif