#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"

class Game {
	int level;
	static int score;
	int moves;
	Board * theBoard;
	bool checkAll(int x, int y, int matchingColour);

	//command line fields
	bool graphics;
	int seed;
	
public:
	
	Game(int moves, int level, int seed, std::ifstream *fin, bool graphics, bool customScript): // Default params need to go at the end
		level(level), moves(moves), graphics(graphics),seed(seed){
			theBoard = new Board();
			theBoard->init(level, seed, fin, customScript);
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
	bool levelWon();
	bool checkMatch(int chain);

	static void increaseScore(int x);

	friend std::ostream &operator<<(std::ostream &out, const Game &g);

};

#endif