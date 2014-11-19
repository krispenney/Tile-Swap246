#include "square.h"

Square::Square(){
	
}

Square::Square(int x, int y, int colour, char type, bool locked, TextDisplay * td):  x(x), y(y), type(type), colour(colour), 
 locked(locked),  td(td) {}

void Square::updateTD(int x, int y, int colour, char type){
	
}

void Square::moveDown(){
	if (above != NULL) {
		std::cerr << "x: " << x << " y: " << y << std::endl;
		int aboveType = above->getType();
		int aboveColour = above->getColour();

		this->setType(aboveType);
		this->setColour(aboveColour);

		td->update(x,y,colour,type, false);

		above->moveDown();
	} else {
		//Generate new stuff for that square
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
