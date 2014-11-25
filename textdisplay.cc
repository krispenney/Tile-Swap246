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

void TextDisplay::update(int x, int y, int colour, char ch, bool locked) {
//	cerr << "locked: " << locked << endl;
	if(locked){//set locked bit
//		cerr << "locking " << x << " " << y << endl;
		theDisplay[x][y*3] = 'l';
	}
	theDisplay[x][(y*3) + 1] = ch;
	theDisplay[x][(y*3) + 2] = colour;
}

//updates the display, unlocks tile
void TextDisplay::unlockUpdate(int x, int y){
	theDisplay[x][y*3] = '_';
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	// cerr << "td.cc" << endl;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			for (int c = 0; c < 3; c++) {
				out << td.theDisplay[x][(y*3) + c];
			}
			out << " ";
		}
		out << endl;
	}
	// cerr << "done in td.cc" << endl;

	return out;
}