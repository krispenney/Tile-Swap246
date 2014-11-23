#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "textdisplay.h"

class Square {
	int x;
	int y;
	char type;
	int colour;	
	int level;
	Square * above;
	bool locked;
	TextDisplay * td;
	
public:
	Square();
	Square(int x, int y, int colour, char type, bool locked, TextDisplay *);
	void updateTD(int x, int y, int colour, char type);
	void moveDown(char c);
	void draw();
	
	void setAbove(Square * above);

	void setColour(int colour);
	int getColour();
	
	void setType(char t);
	char getType();

	void setLevel(int l);
	
};

#endif