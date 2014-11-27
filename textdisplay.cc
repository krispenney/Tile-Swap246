#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(bool graphics) {
	theDisplay = new char *[10];
	this->graphics = graphics;
	
	if(graphics){
		theWindow = new Xwindow;
	}
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
	delete theWindow;
}

void TextDisplay::update(int x, int y, int colour, char type, bool locked) {

	//	cerr << "updating window" << endl;
	if(graphics){
		if(colour == '0'){
			theWindow->fillRectangle(y*50, x*50, 50, 50, colour - '0');
			theWindow->fillRectangle(y*50, x*50, 1, 50, 1);
			theWindow->fillRectangle(y*50, x*50+49, 50, 1, 1);
			theWindow->fillRectangle(y*50, x*50, 50, 1, 1);
			theWindow->fillRectangle(y*50+49, x*50, 1, 50, 1);
			
		}else{
			theWindow->fillRectangle(y*50, x*50, 50, 50, colour - '0' + 1);
		}
		
		if(type == 'h'){//special tiles
			theWindow->fillRectangle(y*50, x*50, 20,50, 5);
		}else if(type == 'v'){
			theWindow->fillRectangle(y*50, x*50, 20,50, 6);
		}else if(type == 'b'){
			theWindow->fillRectangle(y*50, x*50, 20,50, 7);
		}else if(type == 'p'){
			theWindow->fillRectangle(y*50, x*50, 20,50, 8);
		}

	}
	
	
	if(locked){//set locked bit
	//	cerr << "locking " << x << " " << y << endl;
		theDisplay[x][y*3] = 'l';
		
		if(graphics){
			theWindow->fillRectangle(y*50+20, x*50+20, 10, 10, 1);
		}
	}
	theDisplay[x][(y*3) + 1] = type;
	theDisplay[x][(y*3) + 2] = colour;
	


	
	//add things for locked and special tiles
}

//updates the display, unlocks tile
void TextDisplay::unlockUpdate(int x, int y){
	theDisplay[x][y*3] = '_';
	
}

void TextDisplay::setGraphics(bool graphics){
	this->graphics = graphics;
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