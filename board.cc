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
		 *			   Capital letter means used special tile (in matching only)
		 *			   Destroyed tile (to be replaced): D
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
				
				sq->setLevel(level);

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

//checks if valid cooridinates
bool Board::valid(int x, int y){
	if(x >= 0 && x < 10 && y >= 0 && y < 10){
		return true;
	}
	
	return false;
}

//check for L
int Board::checkL(int x, int y, int matchingColour){
	
	if(valid(x+1, y) && valid(x+2, y) && valid(x, y+1) && valid(x, y+2) &&
 	   theBoard[x+1][y].getColour() == matchingColour &&
	   theBoard[x+2][y].getColour() == matchingColour &&
	   theBoard[x][y+1].getColour() == matchingColour &&
	   theBoard[x][y+2].getColour() == matchingColour){//right and down
		cerr << x << " " << y << " right and down" << endl;
		return 0;
	}else if(valid(x+1, y) && valid(x+2, y) && valid(x+2, y+1) && valid(x+2, y+2)
			&&
			 theBoard[x+1][y].getColour() == matchingColour &&
			 theBoard[x+2][y].getColour() == matchingColour &&
			 theBoard[x+2][y+1].getColour() == matchingColour &&
			 theBoard[x+2][y+2].getColour() == matchingColour){//right and up
		return 1;
	}else if(valid(x+1, y+2) && valid(x+2, y+2) && valid(x, y+1) && valid(x, y+2) &&
			 theBoard[x+1][y+2].getColour() == matchingColour &&
			 theBoard[x+2][y+2].getColour() == matchingColour &&
			 theBoard[x][y+1].getColour() == matchingColour &&
			 theBoard[x][y+2].getColour() == matchingColour){//down and left
		return 2;
	}else if(valid(x-1, y+2) && valid(x-2, y+2) && valid(x, y+1) && valid(x, y+2) &&
			 theBoard[x-1][y+2].getColour() == matchingColour &&
			 theBoard[x-2][y+2].getColour() == matchingColour &&
			 theBoard[x][y+1].getColour() == matchingColour &&
			 theBoard[x][y+2].getColour() == matchingColour){//up and left
		return 3;
	}
	
	return -1;//no match
	
}

//Lateral Square
bool Board::checkH(int x, int y, int matchingColour){
	if(valid(x, y+1) && valid(x, y+2) && valid(x, y+3) &&
	   theBoard[x][y+1].getColour() == matchingColour &&
	   theBoard[x][y+2].getColour() == matchingColour &&
	   theBoard[x][y+3].getColour() == matchingColour){
		return true;
	}
	return false;
	
}

//upright square
bool Board::checkU(int x, int y, int matchingColour){
	if(valid(x+1, y) && valid(x+2, y) && valid(x+3, y) &&
	   theBoard[x+1][y].getColour() == matchingColour &&
	   theBoard[x+2][y].getColour() == matchingColour &&
	   theBoard[x+3][y].getColour() == matchingColour){
		return true;
	}
	
	return false;
}

//psychadelic
int Board::checkPsy(int x, int y, int matchingColour){
	if(valid(x+1, y) && valid(x+2, y) && valid(x+3, y) && valid(x+4, y) &&
	   theBoard[x+1][y].getColour() == matchingColour &&
	   theBoard[x+2][y].getColour() == matchingColour &&
	   theBoard[x+3][y].getColour() == matchingColour &&
	   theBoard[x+4][y].getColour() == matchingColour){//vertical
		return 1;
	}else if(valid(x, y+1) && valid(x, y+2) && valid(x, y+3) && valid(x, y+4) &&
			 theBoard[x][y+1].getColour() == matchingColour &&
			 theBoard[x][y+2].getColour() == matchingColour &&
			 theBoard[x][y+3].getColour() == matchingColour &&
			 theBoard[x][y+4].getColour() == matchingColour){//horizontal
		return 2;
	}
	return -1;
}

//basic
int Board::checkBasic(int x, int y, int matchingColour){
	if(valid(x+1, y) && valid(x+2, y) &&
	   theBoard[x+1][y].getColour() == matchingColour &&
	   theBoard[x+2][y].getColour() == matchingColour){//vertical
		return 0;
	}else if(valid(x, y+1) && valid(x, y+2) &&
			 theBoard[x][y+1].getColour() == matchingColour &&
			 theBoard[x][y+2].getColour() == matchingColour){//horizontal
		return 1;
	}
	
	return -1;
}

//changed so that match is found on edge closest to origin
//everything seems to be working now
bool Board::checkMatch(int chain) {
	bool match = false;

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			
			if(theBoard[x][y].getType() == 'D'){
				continue;
			}
			
			int matchingColour = theBoard[x][y].getColour();
			int matchVal = checkPsy(x, y, matchingColour);
			/*if (x == 0) {
				if (y == 0) {
					if (theBoard[x+1][y].getColour() == matchingColour and theBoard[x+2][y].getColour() == matchingColour 
						and theBoard[x][y+1].getColour() == matchingColour and theBoard[x][y+2].getColour() == matchingColour) {
						// L SHAPE right and down
						match = true;
						theBoard[x][y].setType('b');
						theBoard[x+1][y].setType('D');
						theBoard[x+2][y].setType('D');
						theBoard[x][y+1].setType('D');
						theBoard[x][y+2].setType('D');
					} else if (theBoard[x][y+1].getColour() == matchingColour and theBoard[x][y+2].getColour() == matchingColour){
						// 3 match down with x y at top
						match = true;
						theBoard[x][y].setType('D');
						theBoard[x][y+1].setType('D');
						theBoard[x][y+2].setType('D');
					} else if (theBoard[x+1][y].getColour() == matchingColour and theBoard[x+2][y].getColour() == matchingColour) {
						// 3 match sideways with x y and left end
						match = true;
						theBoard[x][y].setType('D');
						theBoard[x+1][y].setType('D');
						theBoard[x+2][y].setType('D');
					}
				} else if (y == 1) {
					if (theBoard[x+1][y].getColour() == matchingColour and theBoard[x+2][y].getColour() == matchingColour 
						and theBoard[x][y+1].getColour() == matchingColour and theBoard[x][y+2].getColour() == matchingColour) {
						// L SHAPE right and down
						match = true;
						theBoard[x][y].setType('b');
						theBoard[x+1][y].setType('D');
						theBoard[x+2][y].setType('D');
						theBoard[x][y+1].setType('D');
						theBoard[x][y+2].setType('D');
					} else if (theBoard[x][y-1].getColour() == matchingColour and theBoard[x][y+1].getColour() == matchingColour
						and theBoard[x][y+2].getColour() == matchingColour) {
						// 4 match with x y being the second one
						theBoard[x][y-1].setType('D');
						theBoard[x][y].setType('h');
						theBoard[x][y+1].setType('D');
						theBoard[x][y+2].setType('D');
					} else if (true) {
						// vertical 3 match in the middle
					} else if () {
						// vertical 3 match at the top
					} else if () {
						// horizontal 3 match at the left
					}
				} else if (y == 8) {
					if () {
						// L up and right
					} else if () {
						// vertical 4, third from the top
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					} else if () {
						// horzontal 3, at the left
					}
				} else if (y == 9) {
					if () {
						// L up and right
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// vertical 3, at the bottom
					}
				} else  {
					if () {
						// vertical 5
					} else if () {
						// L, up and right
					} else if () {
						// L down and right
					} else if () {
						// vertical 4, second from the top
					} else if () {
						// vertical 4, third from the top
					} else if () {
						// vertical 3, at the top
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					} else if () {
						// horizontal 3, at the left
					}
				}
			} else if (x == 2) {
				if (y == 0) {
					if () {
						// L right and down
					} else if () {
						// horizontal 4, second from the left
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// vertical 3, at the top
					}
				} else if (y == 1) {
					if () {
						// L right and down
					} else if () {
						// horizontal 4, second from the left
					} else if () {
						// vertical 4, second from the top
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// vertical 3, at the top
					} else if () {
						// vertical 3, in the middle
					}
				} else if (y == 8) {
					if () {
						// L right and up
					} else if () {
						// horizontal 4, second from the left
					} else if () {
						// vertical 4, second from the bottom
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					}
				} else if (y == 9) {
					if () {
						// L right and up
					} else if () {
						// horizontal 4, second from the left
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					}
				} else {
					if () {
						// Vertical 5
					} else if () {
						// L up and right
					} else if () {
						// L down and right
					} else if () {
						// horizontal 4, second from the left
					} else if () {
						// vertical 4, second from the top
					} else if () {
						// vertical 4, third from the top
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// veritcal 3, at the top
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					}
				}
			} else if (x == 8) {
				if (y == 0) {
					if () {
						// L left and down
					} else if () {
						// horizontal 4, third from the left
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, at the top
					}
				} else if (y == 1) {
					if () {
						// L left and down
					} else if () {
						// horizontal 4, third from the left
					} else if () {
						// vertical 4, second from the top
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, at the top
					} else if () {
						// vertical 3, in the middle
					}
				} else if (y == 8) {
					if () {
						// L left and up
					} else if () {
						// horizontal 3, third from the left
					} else if () {
						// vertical 4, third from the top
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					}
				} else if (y == 9) {
					if () {
						// L left and up
					} else if () {
						// horizontal 4, third from the left
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, at the bottom
					}
				} else {
					if () {
						// vertical 5
					} else if () {
						// L left and up
					} else if () {
						// L left and down
					} else if () {
						// horizontal 4, third from the left
					} else if () {
						// vertical 4, second from the top
					} else if () {
						// vertical 4, third from the top
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, at the top
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					}
				}
			} else if (x == 9) {
				if (y == 0) {
					if () {
						// L left and down
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, at the top
					}
				} else if (y == 1) {
					if () {
						// L left and down
					} else if () {
						// vertical 4, second from the top
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, at the top
					} else if () {
						// vertical 3, in the middle
					}
				} else if (y == 8) {
					if () {
						// L left and up
					} else if () {
						// vertical 4, third from the top
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					}
				} else if (y == 9) {
					if () {
						// L left and up
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, at the bottom
					}
				} else {
					if () {
						// vertical 5
					} else if () {
						// L left and down
					} else if () {
						// L left and up
					} else if () {
						// vertical 4, second from the top
					} else if () {
						// vertical 4, third from the top
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// vertical 3, at the top
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					}
				}
			} else {
				if (y == 0) {
					if () {
						// Horizontal  5
					} else if () {
						// L left and down
					} else if () {
						// L right and down
					} else if () {
						// Horizontal 4, second from the left
					} else if () {
						// Horizontal 4, third from the left
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// vertical 3, at the top
					}
				} else if (y == 1) {
					if () {
						// Horizontal  5
					} else if () {
						// L left and down
					} else if () {
						// L right and down
					} else if () {
						// Horizontal 4, second from the left
					} else if () {
						// Horizontal 4, third from the left
					} else if () {
						// vertical 4, second from the top
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// vertical 3, at the top
					} else if () {
						// vertical 3, in the middle
					}
				} else if (y == 8) {
					if () {
						// Horizontal 5
					} else if () {
						// L left and up
					} else if () {
						// L right and up
					} else if () {
						// Horizontal 4, second from the left
					} else if () {
						// Horizontal 4, third from the left
					} else if () {
						// vertical 4, third from the top
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// vertical 3, in the middle
					} else if () {
						// vertical 3, at the bottom
					}	
				} else if (y == 9) {
					if () {
						// Horizontal  5
					} else if () {
						// L left and up
					} else if () {
						// L right and up
					} else if () {
						// Horizontal 4, second from the left
					} else if () {
						// Horizontal 4, third from the left
					} else if () {
						// horizontal 3, at the right
					} else if () {
						// horizontal 3, in the middle
					} else if () {
						// horizontal 3, at the left
					} else if () {
						// vertical 3, at the bottom
					}
				} else {
					if (theBoard[x+2][y].getColour() == matchingColour and theBoard[x+1][y].getColour() == matchingColour
						and theBoard[x-1][y].getColour() == matchingColour and theBoard[x-2][y].getColour() == matchingColour) {
						// Horizontal match of 5
						match = true;
						theBoard[x+2][y].setType('D');
						theBoard[x+1][y].setType('D');
						theBoard[x][y].setType('p');
						theBoard[x-1][y].setType('D');
						theBoard[x-2][y].setType('D');
					} else if (theBoard[x][y+2].getColour() == matchingColour and theBoard[x][y+1].getColour() == matchingColour
						and theBoard[x][y-1].getColour() == matchingColour and theBoard[x][y-1].getColour() == matchingColour) {
						//Vertical match of 5
						match = true;
						theBoard[x][y+2].setType('D');
						theBoard[x][y+1].setType('D');
						theBoard[x][y].setType('p');
						theBoard[x][y-1].setType('D');
						theBoard[x][y-2].setType('D');
					} else if (theBoard[x-2][y].getColour() == matchingColour and theBoard[x-1][y].getColour() == matchingColour
						and theBoard[x][y-2].getColour() == matchingColour and theBoard[x][y-1].getColour() == matchingColour) {
						// left and up L
						match = true;
						theBoard[x-2][y].setType('D');
						theBoard[x-1][y].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x][y-1].setType('D');
						theBoard[x][y-2].setType('D');
					} else if (theBoard[x-2][y].getColour() == matchingColour and theBoard[x-1][y].getColour() == matchingColour
						and theBoard[x][y+1].getColour() == matchingColour and theBoard[x][y+2].getColour() == matchingColour) {
						// left and down L
						match = true;
						theBoard[x-2][y].setType('D');
						theBoard[x-1][y].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x][y+1].setType('D');
						theBoard[x][y+2].setType('D');
					} else if (theBoard[x+2][y].getColour() == matchingColour and theBoard[x+1][y].getColour() == matchingColour
						and  theBoard[x][y-2].getColour() == matchingColour and theBoard[x][y-1].getColour() == matchingColour) {
						// right and up L
						match = true;
						theBoard[x+2][y].setType('D');
						theBoard[x+1][y].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x][y-1].setType('D');
						theBoard[x][y-2].setType('D');
					} else if (theBoard[x+2][y].getColour() == matchingColour and theBoard[x+1][y].getColour() == matchingColour
						and theBoard[x][y+1].getColour() == matchingColour and theBoard[x][y+2].getColour() == matchingColour) {
						// right and down L
						match = true;
						theBoard[x+2][y].setType('D');
						theBoard[x+1][y].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x][y+1].setType('D');
						theBoard[x][y+2].setType('D');
					} else if (theBoard[x-1][y].getColour() == matchingColour and theBoard[x+1][y].getColour() == matchingColour
						and theBoard[x+2][y].getColour() == matchingColour) {
						// Horizontal match of 4, x y second from the left
						match = true;
						theBoard[x+1][y].setType('D');
						theBoard[x][y].setType('h');
						theBoard[x-1][y].setType('D');
						theBoard[x-2][y].setType('D');
					} else if (theBoard[x+2][y].getColour() == matchingColour and theBoard[x+1][y].getColour() == matchingColour
						and theBoard[x-1][y].getColour() == matchingColour) {
						//Horizontal match of 4, x y second from the right
						match = true;
						theBoard[x+2][y].setType('D');
						theBoard[x+1][y].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x-1][y].setType('D');
					} else if (theBoard[x][y-1].getColour() == matchingColour and theBoard[x][y+1].getColour() == matchingColour
						and theBoard[x][y+2].getColour() == matchingColour) {
						// Vertical match of 4, x y second from the top
						match = true;
						theBoard[x][y+1].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x][y-1].setType('D');
						theBoard[x][y-2].setType('D');
					} else if (theBoard[x][y-2].getColour() == matchingColour and theBoard[x][y-1].getColour() == matchingColour
						and theBoard[x][y+1].getColour() == matchingColour) {
						// Vertical match of 4, x y third from the top
						match = true;
						theBoard[x][y+2].setType('D');
						theBoard[x][y+1].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x][y-1].setType('D');
					} else if (theBoard[x][y-2].getColour() == matchingColour and theBoard[x][y-1].getColour() == matchingColour) {
						// vertical 3 match, x y at top
						match == true;
						theBoard[x][y-2].setType('D');
						theBoard[x][y-1].setType('D');
						theBoard[x][y].setType('D');
					} else if (theBoard[x][y-1].getColour() == matchingColour and theBoard[x][y+1].getColour() == matchingColour) {
						// vertical 3 match, x y in middle
						match = true;
						theBoard[x][y-1].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x][y+1].setType('D');
					} else if (theBoard[x][y+1].getColour() == matchingColour and theBoard[x][y+2].getColour() == matchingColour) {
						// vertical 3 match, x y at bottom
						match = true;
						theBoard[x][y+2].setType('D');
						theBoard[x][y+1].setType('D');
						theBoard[x][y].setType('D');
					} else if (theBoard[x+1][y].getColour() == matchingColour and theBoard[x+2][y].getColour() == matchingColour) {
						// horizontal 3 match, x y at left
						match = true;
						theBoard[x][y].setType('D');
						theBoard[x+1][y].setType('D');
						theBoard[x+2][y].setType('D');
					} else if (theBoard[x-1][y].getColour() == matchingColour and theBoard[x+1][y].getColour() == matchingColour) {
						// horizontal 3 match, x y in middle
						match = true;
						theBoard[x-1][y].setType('D');
						theBoard[x][y].setType('D');
						theBoard[x+1][y].setType('D');
					} else if (theBoard[x-1][y].getColour() == matchingColour and theBoard[x-2][y].getColour() == matchingColour) {
						// horizontal 3 match, x y at right
						match = true;
						theBoard[x-2][y].setType('D');
						theBoard[x-1][y].setType('D');
						theBoard[x][y].setType('D');
					}
				}*/
			
			if(matchVal != -1){//psychadelic
				cerr << "psychadelic square" << endl;
				
				if(matchVal == 1){//vertical
					cerr << "vertical" << endl;
					theBoard[x][y].setType('D');
					theBoard[x+1][y].setType('D');
					theBoard[x+2][y].setType('p');
					theBoard[x+3][y].setType('D');
					theBoard[x+4][y].setType('D');
					
				}else if(matchVal == 2){//horizontal
					cerr << "horizontal" << endl;
					theBoard[x][y].setType('D');
					theBoard[x][y+1].setType('D');
					theBoard[x][y+2].setType('p');
					theBoard[x][y+3].setType('D');
					theBoard[x][y+4].setType('D');
				}
				
				match = true;
				continue;
			}else if(checkH(x, y, matchingColour)){//lateral
				cerr << "lateral square" << endl;
				
				theBoard[x][y].setType('D');
				theBoard[x][y+1].setType('h');//could add random to select x+1 or x+2
				theBoard[x][y+2].setType('D');
				theBoard[x][y+3].setType('D');
				
				match = true;
				continue;
				
			}else if(checkU(x, y, matchingColour)){//Upright
				cerr << "upright square" << endl;
				
				theBoard[x][y].setType('D');
				theBoard[x+1][y].setType('v');//could add random to select x+1 or x+2
				theBoard[x+2][y].setType('D');
				theBoard[x+3][y].setType('D');
				
				match = true;
				continue;
			}
			
			
			matchVal = checkL(x, y, matchingColour);//L
			
			if(matchVal != -1){
				cerr << "Unstable square" << endl;
				
				if(matchVal == 0){//down and right
					cerr << "Down and right" << endl;
					theBoard[x][y].setType('b');
					theBoard[x+1][y].setType('D');
					theBoard[x+2][y].setType('D');
					theBoard[x][y+1].setType('D');
					theBoard[x][y+2].setType('D');
				}else if(matchVal == 1){//up and right
					cerr << "up and right" << endl;
					theBoard[x][y].setType('D');
					theBoard[x+1][y].setType('D');
					theBoard[x+2][y].setType('b');
					theBoard[x+2][y+1].setType('D');
					theBoard[x+1][y+2].setType('D');
					
				}else if(matchVal == 2){//down and left
					cerr << "down and left" << endl;
					theBoard[x][y].setType('D');
					theBoard[x][y+1].setType('D');
					theBoard[x][y+2].setType('b');
					theBoard[x+1][y+2].setType('D');
					theBoard[x+2][y+2].setType('D');
					
				}else if(matchVal == 3){//up and left
					cerr << "up and left" << endl;
					theBoard[x][y].setType('D');
					theBoard[x][y+1].setType('D');
					theBoard[x][y+2].setType('b');
					theBoard[x+1][y+2].setType('D');
					theBoard[x+2][y+2].setType('D');
					
				}
				
				match = true;
				continue;
			}
			
			
			matchVal = checkBasic(x, y, matchingColour);//basic
			
			if(theBoard[x][y].getType() == '_' && matchVal != -1){
				cerr << "Basic match" << endl;
				
				if(matchVal == 0){
					cerr << "vertical" << endl;
					theBoard[x][y].setType('D');
					theBoard[x+1][y].setType('D');
					theBoard[x+2][y].setType('D');
					
					
				}else if(matchVal == 1){
					cerr << "horizontal" << endl;
					theBoard[x][y].setType('D');
					theBoard[x][y+1].setType('D');
					theBoard[x][y+2].setType('D');
					
					
				}
				match = true;
			}
			/*if(match){
				cout << x << " " << y << endl;
				match = false;
			}*/
		}
	}
	
	//special matches ...

	if (match) {
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				// Use all matched special blocks
			}
		}
	}

	if (match) {
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				if (theBoard[x][y].getType() == 'D') {
					// Replace all destroyed tiles
					theBoard[x][y].moveDown();
				}
			}
		}
	}


	return match; //Change this to actually check when I dont feel sick
}


ostream &operator<<(ostream &out, const Board &b){
	// std::cerr << "here in board.cc" << std::endl;
	out << *b.td;
	return out;
}