#include "board.h"
#include "square.h"
#include "textdisplay.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

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
				
				Square * sq = new Square(i, j, colour, type, locked, td);
				if (i != 0) {
					sq->setAbove(&theBoard[i-1][j]);
				} else {
					sq->setAbove(NULL);
				}

				theBoard[i][j] = *sq;

				update(i, j, colour, type, locked);
			}
		}
		
		theBoard[5][5].moveDown();

	}else if(level == 1){
		
		int specialCount = 1;
		locked = false;
		srand(time(NULL));
		/*if(filename != ""){ add in scriptfile later
		
		}else{
			
		}*/
		
		for(int i = 0; i < 10; i++){
			theBoard[i] = new Square[10];
			int randColour = 0;
			int randType = 0;
			
			for(int j = 0; j < 10; j++){
				
				//generate colour
				
				randColour = rand()%6;//generate for colour
				
				if(randColour == 0 || randColour == 1){//1/3 for white
					colour = '0';
				}else if(randColour == 2 || randColour == 3){//1/3 for red
					colour = '1';
				}else if(randColour == 4){//1/6 for green
					colour = '2';
				}else if(randColour == 5){//1/6 for blue
					colour = '3';
				}
				
				if(specialCount == 5){//every 5th is special
					randType = rand()%5;
					
					if(randType == 0){//basic
						type = '_';
					}else if(randType == 1){//lateral
						type = 'h';
					}else if(randType == 2){//upright
						type = 'v';
					}else if(randType == 3){//unstable
						type = 'b';
					}else if(randType == 4){//psychadelic
						type = 'p';
					}
					
					specialCount = 1;
				}else{
					type = '_';
					specialCount++;
				}
				
				Square * sq = new Square(i, j, colour, type, locked, td);
				if (i != 0) {
					sq->setAbove(&theBoard[i-1][j]);
				} else {
					sq->setAbove(NULL);
				}
				
				theBoard[i][j] = *sq;
				
				update(i, j, colour, type, locked);
			}
		}
		
		
	}else if(level == 2){
		
		int totalLocked = 20;//20% locked
		srand(time(NULL));
		type = '_';
		/*if(filename != ""){ add in scriptfile later
			
		 }else{
			
		 }*/
		for(int i = 0; i < 10; i++){
			theBoard[i] = new Square[10];
			int randColour = 0;
			
			for(int j = 0; j < 10; j++){
				bool lock = rand()%2;
				randColour = rand()%4;//generate for colour
				
				if(lock && totalLocked > 0){
			//		cerr << "locked:" << i << " " << j << endl;
			//		cerr << totalLocked << endl;
			
					totalLocked--;
				}else{
					lock = false;
				}
				//generate colour
				
				if(randColour == 0){//1/3 for white
					colour = '0';
				}else if(randColour == 1){//1/3 for red
					colour = '1';
				}else if(randColour == 2){//1/6 for green
					colour = '2';
				}else if(randColour == 3){//1/6 for blue
					colour = '3';
				}
				Square * sq = new Square(i, j, colour, '_', lock, td);
				if (i != 0) {
					sq->setAbove(&theBoard[i-1][j]);
				} else {
					sq->setAbove(NULL);
				}
				
				theBoard[i][j] = *sq;
				
				update(i, j, colour, type, lock);
			}
			
		}

		
	}
	//more as levels increase
}

//get square at x, y
Square *Board::getSquare(int x, int y){
	return &theBoard[x][y];
}

//update the board
void Board::update(int x, int y, int colour, char ch, bool lock){
	td->update(x, y, colour, ch, lock);
}

//swaps the colour and type of s1 and s2, need to check for match and account for moves
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