#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"

class Game {
	int level;
	static int score;
	int moves;
	Board * theBoard;
	bool checkAll(int x, int y, int matchingColour);
public:
	
	Game(int moves, int level = 0): // Default params need to go at the end
		level(level), moves(moves){
			theBoard = new Board();
			theBoard->init(this->level);
		}
	
	~Game();
	
	bool checkSwap(int x, int y, int dir);
	void swap(int x1, int y1, int x2, int y2);
	
	int getLevel();
	bool hint(bool print);
	void changeLevel(bool up);// replaces level up and down
	void scramble();
	void decMoves();
	void reset();
	static void increaseScore(int x);
	bool levelWon();
	bool checkMatch(int chain);


	friend std::ostream &operator<<(std::ostream &out, const Game &g);

};

#endif