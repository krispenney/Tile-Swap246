#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>
#include "window.h"

class TextDisplay {
	char **theDisplay;
	Xwindow *theWindow;
	bool graphics;
public:
	TextDisplay(bool graphics);
	
	void update(int x, int y, int colour, char ch, bool locked);
	void unlockUpdate(int x, int y);
	void setGraphics(bool graphics);
	
	~TextDisplay();

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

};

#endif