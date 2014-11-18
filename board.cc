#include "board.h"

using namespace std;

Board::Board(){
	
}

Board::~Board(){
	delete td;
	delete theBoard;
}

void init(int level){
	
}


// This isnt going to work because these are private fields
void swap(Square * s1, Square * s2){
	int tmpColour = s1->colour;
	int tmpType = s2->colour;
	
	s1->colour = s2->colour;
	s1->type = s2->type;
	
	s2->colour = tmpColour;
	s2->type = tmpType;
	
	//td->notify(); notify board
	
}

ostream &operator<<(ostream &out, const Board &b){
	out << b.td;
	return out;
}