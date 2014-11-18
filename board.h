#ifndef __BOARD_H__
#define __BOARD_H__

#include "square.h"
#include "textdisplay.h"

class Board {
	TextDisplay * td;
	Square **theBoard;
public:
	Board();
	void init(int level);

	void swap(Square * s1, Square * s2);
	~Board();

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
	
};

#endif