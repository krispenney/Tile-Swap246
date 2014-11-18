#include "board.h"

using namespace std;

Board::Board(){
	
}

Board::~Board(){
	delete td;
	delete theBoard;
}

void init(int level, string filename = ""){
	
	string zeroFName = "sequence.txt";
	bool locked = false;
	char type;
	int colour;
	
	delete theBoard;
	delete td;
	
	if(level == 0){
		ifstream fin(zeroFName);
		
		/* colours:    Squares:
		 * White: 0    Basic: _
		 * Red: 1      Lateral: h
		 * Green: 2    Upright: v
		 * Blue: 3     Unstable: b
		 *             Psychedelic: p
		 */
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 10; j++){
				fin >> type >> colour;
				
				theBoard[i][j] = new Square(colour, type, false, td);
				td->update(i, j, colour + '0', type);
			}
		}
		
	}else if(level == 1){
		
		/*if(filename != ""){ add in scriptfile later
			
		}else{
			
		}*/
		
		
		
	}else if(level == 2){
		
		/*if(filename != ""){ add in scriptfile later
			
		 }else{
			
		 }*/
		
		
		
	}
	//more as levels increase
}


// This isnt going to work because these are private fields
void swap(Square * s1, Square * s2){
	int tmpColour = s1->getColour();
	int tmpType = s2->getType();
	
	s1->setColour(s2->getColour());
	s1->setType(s2->getType());
	
	s2->setColour = tmpColour;
	s2->setType = tmpType;
	
	//td->notify(); notify board
	
}

ostream &operator<<(ostream &out, const Board &b){
	out << b.td;
	return out;
}