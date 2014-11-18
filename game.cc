#include "game.h"

using namespace std;

score = 0;
const int MAXLEVELS = 2;

//dtor
Game::~Game(){
	delete theBoard;
}

//later
void Game::hint(){
	return;
}

//will rely on hint
void Game::scramble(){
	return;
}

//clear board and create new at the same level
void Game::reset(){
	//delete theBoard;
	
	theBoard = theBoard->init(level);
}

//combine level up and down
void Game::changeLevel(bool up){
	
	if(up && level == MAXLEVELS){//don't change
		return;
	}else if(up && level == 0){
		return;
	}
	
	if(up){//level up
		level++;
	}else{//down
		level--;
	}
	
	//reinitialize board
	theBoard->init(level);
}

bool Game::levelWon(){
	
}

//overload operator<< called to board
ostream &operator<<(std::ostream &out, const Game &g){
	
	//write header output
	
	out << g.theBoard;
	return out;
}