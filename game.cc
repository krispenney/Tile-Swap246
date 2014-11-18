#include "game.h"
#include "board.h"

using namespace std;

int Game::score = 0;
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

bool Game::levelWon(){
	return false;
}

//overload operator<< called to board
ostream &operator<<(std::ostream &out, const Game &g){
	
	//write header output
	
	// std::cerr << "here in game.cc" << std::endl;
	out << *g.theBoard;
	return out;
}