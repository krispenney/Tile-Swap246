#include "game.h"
#include "board.h"
#include <iomanip>

using namespace std;

int Game::score = 0;
const int MAXLEVELS = 2;

//dtor
Game::~Game(){
	delete theBoard;
}

//later
bool Game::hint(){
	
	
	
	return false;//will return false if no hint -> no moves left
}

//will rely on hint
void Game::scramble(){
	
	//check if no moves left 
	
	srand(time(NULL));
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			int randX = rand()%10;
			int randY = rand()%10;
			while(randX != i && randY != j){//ensure don't select the same
				randX = rand()%10;
				randY = rand()%10;
			}
			swap(i, j, randX, randY);
			
		}
	}
	
}

//clear board and create new at the same level
void Game::reset(){
	delete theBoard;
	
	theBoard = new Board();
	theBoard->init(level);
}

//combine level up and down
void Game::changeLevel(bool up){
	
	if(up && level == MAXLEVELS){//don't change
		return;
	}else if(!up && level == 0){ //Changed this to down and level = 0
		return;
	}
	
	if(up){//level up
		level++;
	}else{//down
		level--;
	}
	
	delete theBoard;
	theBoard = new Board();
	theBoard->init(level);
}

//swap squares, update board
void Game::swap(int x1, int y1, int x2, int y2){
	
	theBoard->swap(theBoard->getSquare(x1, y1), theBoard->getSquare(x2, y2));
	
	int colour1 = theBoard->getSquare(x1, y1)->getColour();
	int type1 = theBoard->getSquare(x1, y1)->getType();
	int colour2 = theBoard->getSquare(x2, y2)->getColour();
	int type2 = theBoard->getSquare(x2, y2)->getType();
	
	theBoard->update(x1, y1, colour1, type1, false);//doesn't affect locked state
	theBoard->update(x2, y2, colour2, type2, false);
	
	
}

//cleans up swap
bool Game::checkSwap(int x, int y, int dir){
	if(dir == 0){//north
		if(x-1 < 0){
			cout << "Invalid switch!" << endl;
		}else{
			swap(x, y, x-1, y);
			return true;
		}
	}else if(dir == 1){//south
		if(x+1 > 9){
			cout << "Invalid switch!" << endl;
		}else{
			swap(x, y, x+1, y);
			return true;
		}
	}else if(dir == 2){//west
		if(y-1 < 0){
			cout << "Invalid switch!" << endl;
		}else{
			swap(x, y, x, y-1);
			return true;
		}
		
	}else if(dir == 3){//east
		if(y+1 > 9){
			cout << "Invalid switch!" << endl;
		}else{
			swap(x, y, x, y+1);
			return true;
		}
	}
	
	return false;
}

//returns current level
int Game::getLevel(){
	return level;
}

bool Game::levelWon(){
	//add other conditions
	
	return false;
}

bool Game::checkMatch() {
	return theBoard->checkMatch();
}

//decrement moves
void Game::decMoves(){
	moves--;
}

//overload operator<< called to board
ostream &operator<<(ostream &out, const Game &g){
	
	//write header output
	out << setw(18) << left << "Level:" << right << g.level << endl;
	out << setw(18) << left << "Score:" << right << g.score << endl;
	out << setw(18) << left << "Moves Remaining:" << right << g.moves << endl;
	out << setw(18) << left << "High Score:" << right << 0 << endl;//change to high score
	out << "------------------" << endl << endl;
	
	
	// std::cerr << "here in game.cc" << std::endl;
	out << *g.theBoard;
	return out;
}