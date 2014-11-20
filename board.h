#ifndef __BOARD_H__
#define __BOARD_H__

#include "square.h"
#include "textdisplay.h"
#include <cstdlib>
#include <ctime>


class Board {
	TextDisplay * td;
	Square **theBoard;
public:
	Board();
	void init(int level, std::string filename = "");
	
	Square *getSquare(int x, int y);
	
	void update(int x, int y, int colour, char ch, bool locked);
	void swap(Square * s1, Square * s2);
	
	bool checkMatch(int chain);

	~Board();

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
	
};

#endif