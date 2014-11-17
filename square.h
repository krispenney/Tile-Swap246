#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "textdisplay.h"

class Square {
	int type;
	int color;
	Square * above;
	TextDisplay * td;
	bool locked;
public:
	Square();
	void updateTD(int x, int y, char ch);
	void moveDown();
	void draw();
};

#endif