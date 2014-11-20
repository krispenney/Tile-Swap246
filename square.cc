#include "square.h"

#include <cstdlib>
#include <ctime>

Square::Square(){
	
}

Square::Square(int x, int y, int colour, char type, bool locked, TextDisplay * td):  x(x), y(y), type(type), colour(colour), 
 locked(locked),  td(td) {}

void Square::updateTD(int x, int y, int colour, char type){
	td->update(x, y, colour, type, false);
}

void Square::moveDown(){
	if (above != NULL) {
		// std::cerr << "x: " << x << " y: " << y << std::endl;
		int aboveType = above->getType();
		int aboveColour = above->getColour();

		this->setType(aboveType);
		this->setColour(aboveColour);

		td->update(x,y,colour,type, false);

		above->moveDown();
	} else {
		int colour = 0;
		int randColour = 0;
		//Generate new stuff for that square
		if (level == 0) {
			randColour = rand()%6;
			if(randColour == 0 || randColour == 1){//1/3 for white
				colour = '0';
			}else if(randColour == 2 || randColour == 3){//1/3 for red
				colour = '1';
			}else if(randColour == 4){//1/6 for green
				colour = '2';
			}else if(randColour == 5){//1/6 for blue
				colour = '3';
			}
		}
		this->setType('_');
		this->setColour(colour);
		updateTD(x,y, colour, '_');
	}
}

void Square::draw(){
	
}

void Square::setAbove(Square * above) {
	this->above = above;
}

void Square::setColour(int colour){
	this->colour = colour;
}
int Square::getColour(){
	return colour;
}

void Square::setType(char t){
	type = t;
}
char Square::getType(){
	return type;
}

void Square::setLevel(int level) {
	this->level = level;
}
