#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>

class TextDisplay {
	char **theDisplay;

public:
	TextDisplay();
	void update(int x, int y, int colour, char ch);

	~TextDisplay();

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

};

#endif