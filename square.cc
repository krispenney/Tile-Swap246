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

void Square::moveDown(char c){
//		std::cerr << "In Movedown" << std::endl;
	//std::cerr<< "Char c: " << (c == '\0') << std::endl;
	if (above != NULL) {
//		 std::cerr << "x: " << x << " y: " << y << std::endl;
		int aboveType = above->getType();
		int aboveColour = above->getColour();

		this->setType(aboveType);
		this->setColour(aboveColour);

		td->update(x,y,colour,type, false);
	//	std::cerr << "calling movedown" << std::endl;
		above->moveDown(c);
	} else {
		int colour = 0;
		int randColour = 0;
		//Generate new stuff for that square

		if (c == '\0' && level == 1) {
			std::cerr << "generating for level 1" << std::endl;
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
			std::cerr << "colour: " << colour << std::endl;
		}else if(c == '\0' && level == 2){
		//	std::cerr << "generating for level 2" << std::endl;
			randColour = rand()%4;
			if(randColour == 0){
				colour = '0';
			}else if(randColour == 1){
				colour = '1';
			}else if(randColour == 2){
				colour = '2';
			}else if(randColour == 3){
				colour = '3';
			}
		}else if(c != '\0'){
			colour = c;
	//		std::cerr <<"placing character" << std::endl;
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
