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
			theBoard = new Board();
			theBoard->init(this->level);
		}
	
	~Game();
	
	void swap(int x1, int y1, int x2, int y2);
	
	int getLevel();
	void hint();
	void changeLevel(bool up);// replaces level up and down
	void scramble();
	void reset();
	static void increaseScore(int x);
	bool levelWon();
	bool checkMatch();


	friend std::ostream &operator<<(std::ostream &out, const Game &g);

};

#endif