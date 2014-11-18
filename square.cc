#include "square.h"

Square::Square(){
	
}

Square::Square(int colour, char type, bool locked, TextDisplay * td): type(type), colour(colour), 
locked(locked), td(td) {}

void Square::updateTD(int x, int y, int colour, char type){
	
}

void Square::moveDown(){
	
}

void Square::draw(){
	
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