#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"

class Game {
	int level;
	static int score;
	int moves;
	Board * theBoard;
public:
	
	Game(int level = 0, int moves, Board *newBoard):
		level(level), moves(moves), theBoard(newBoard){}
	
	~Game();
	void hint();
	void changeLevel();// replaces level up and down
	void scramble();
	void restart();
	static void increaseScore(int x);
	bool levelWon();


	friend std::ostream &operator<<(std::ostream &out, const Game &g);

};

#endif