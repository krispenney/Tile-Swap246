#ifndef __BOARD_H__
#define __BOARD_H__

#include "square.h"
#include "textdisplay.h"
#include <cstdlib>



class Board {
	TextDisplay * td;
	Square **theBoard;
	
public:
	Board();
	void init(int level, std::string filename, int seed);
	
	Square *getSquare(int x, int y);
	

	void explode(int x, int y, char type, int size = 3);

	
	void update(int x, int y, int colour, char ch, bool locked);
	void swap(Square * s1, Square * s2);
	bool valid(int x, int y);
	
	int checkL(int x, int y, int matchingColour);
	bool checkH(int x, int y, int matchingColour);
	bool checkU(int x, int y, int matchingColour);
	int checkPsy(int x, int y, int matchingColour);
	int checkBasic(int x, int y, int matchingColour);
	
	bool checkMatch(int chain);

	~Board();

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
	
};

#endif