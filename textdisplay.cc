#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay() {
	theDisplay = new char *[10];

	for (int i = 0; i < 10; ++i) {
		theDisplay[i] = new char[30];
	}

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 30; y++) {
			theDisplay[x][y] = '_';
		}
	}

}

TextDisplay::~TextDisplay() {
	for(int i = 0; i < 10; i++){
		delete theDisplay[i];
	}
	delete [] theDisplay;
}

void TextDisplay::update(int x, int y, int colour, char ch) {
	theDisplay[x][(y*3) + 1] = ch;
	theDisplay[x][(y*3) + 2] = colour;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	// cerr << "td.cc" << endl;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			for (int c = 0; c < 3; c++) {
				// out << td.theDisplay[0][0];
				out << td.theDisplay[x][(y*3) + c];
			}
			out << " ";
		}
		out << endl;
	}
	// cerr << "done in td.cc" << endl;

	return out;
}