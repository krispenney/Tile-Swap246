#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "textdisplay.h"

class Square {
	char type;
	int colour;	
	Square * above;
	bool locked;
	TextDisplay * td;
	
public:
	Square();
	Square(int colour, char type, bool locked, TextDisplay *);
	void updateTD(int x, int y, int colour, char type);
	void moveDown();
	void draw();
	
	void setColour(int colour);
	int getColour();
	
	void setType(char t);
	char getType();
};

#endif