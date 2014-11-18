#include "board.h"
#include "square.h"
#include "textdisplay.h"
#include <string>
#include <fstream>

using namespace std;

Board::Board(): td(NULL), theBoard(NULL){}

Board::~Board(){
	delete td;
	
	for(int i = 0; i < 10; i++){
		delete theBoard[i];
	}
	
	delete [] theBoard;
}

void Board::init(int level, string filename){
	
	string zeroFName = "sequence.txt";
	bool locked = false;
	char type;
	char colour;
	char lock;
	
	if(theBoard != NULL){
		delete theBoard;
	}
	if(td != NULL){
		delete td;
	}
	
	theBoard = new Square *[10];
	td = new TextDisplay();
	
	if(level == 0){
		ifstream fin(zeroFName.c_str());
		
		/* colours:    Squares:
		 * White: 0    Basic: _
		 * Red: 1      Lateral: h 	
		 * Green: 2    Upright: v
		 * Blue: 3     Unstable: b
		 *             Psychedelic: p
		 */
		
		for(int i = 0; i < 10; i++){
			
			theBoard[i] = new Square[10];
			
			for(int j = 0; j < 10; j++){
				fin >> lock >> type >> colour;
				
				Square * sq = new Square(colour, type, locked, td);

				theBoard[i][j] = *sq;

				// cerr << lock << type << colour << endl;

				td->update(i, j, colour, type);
				// fin >> lock;
			}
		}
		
	}else if(level == 1){
		
		/*if(filename != ""){ add in scriptfile later
			
		}else{
			
		}*/
		
		for(int i = 0; i < 10; i++){
			theBoard[i] = new Square[10];
			
			for(int j = 0; j < 10; j++){
					
			}
		}
		
		
	}else if(level == 2){
		
		/*if(filename != ""){ add in scriptfile later
			
		 }else{
			
		 }*/
		
		
		
	}
	//more as levels increase
}

Square *Board::getSquare(int x, int y){
	return &theBoard[x][y];
}

void Board::update(int x, int y, int colour, char ch){
	td->update(x, y, colour, ch);
}

void Board::swap(Square * s1, Square * s2){
	
	int tmpColour = s1->getColour();
	int tmpType = s1->getType();
	
	/*cout << tmpColour <<endl;
	cout << tmpType << endl;*/
	
	s1->setColour(s2->getColour());
	s1->setType(s2->getType());
	
	s2->setColour(tmpColour);
	s2->setType(tmpType);

}

ostream &operator<<(ostream &out, const Board &b){
	// std::cerr << "here in board.cc" << std::endl;
	out << *b.td;
	return out;
}