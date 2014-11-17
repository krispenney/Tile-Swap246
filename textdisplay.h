#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>

class TextDisplay {
	char **theDisplay;
	const int gridSize;

public:
	TextDisplay();
	void update(int x, int y, char ch);

	~TextDisplay();

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

};

#endif