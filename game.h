#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"

class Game {
	int level;
	static int score;
	int moves;
	Board * theBoard;
public:
	
	Game(int moves, int level = 0): // Default params need to go at the end
		level(level), moves(moves){
			Game::score = 0;
			theBoard = new Board();
		}
	
	~Game();
	void hint();
	void changeLevel(bool up);// replaces level up and down
	void scramble();
	void reset();
	static void increaseScore(int x);
	bool levelWon();


	friend std::ostream &operator<<(std::ostream &out, const Game &g);

};

#endif