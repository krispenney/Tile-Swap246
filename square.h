#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "textdisplay.h"

class Square {
	char type;
	int colour;
	int x;
	int y;
	
	Square * above;
	TextDisplay * td;
	bool locked;
	
public:
	Square();
	void updateTD(int x, int y, int colour, char type);
	void moveDown();
	void draw();
};

#endif