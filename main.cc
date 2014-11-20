#include <iostream>

// #include "board.h"
#include "game.h"
// #include "square.h"
// #include "textdisplay.h"

using namespace std;

Game * theGame = new Game(10);

int main() {
	
	string cmd;
	int x;
	int y;
	int dir;
	const int MAXLEVELS = 2;
	
	// std::cerr << "here" << std::endl;
	cout << *theGame << endl;
	
	while(1){
		
		cin >> cmd;
		if(cin.eof()){
			break;
		}else if(cmd == "switch"){//needs to check for match
			cin >> x >> y >> dir;
			bool match = false;
			int chain = 1;
			
			if(theGame->checkSwap(x, y, dir)){
				match = theGame->checkMatch(chain);
			}
			
			if (match) {
				while (match) {
					cerr << "I HAVE A LOOPING MATCH~~~" << endl;
					match = theGame->checkMatch(chain);
					chain++;
				}
				theGame->decMoves();
			} else {
				// cerr << "no match made plz" << endl;
				// NO MATCH MADE, revert last move
			}
		
		}else if(cmd == "levelup"){
			if(theGame->getLevel() != MAXLEVELS){
				theGame->changeLevel(true);
				
			}else{
				cout << "No more levels" << endl;
			}
			cout << "Playing level: " << theGame->getLevel() << endl;
			
		}else if(cmd == "leveldown"){
			if(theGame->getLevel() > 0){
				theGame->changeLevel(false);
				
			}else{
				cout << "No More levels" << endl;
			}
			cout << "Playing level: " << theGame->getLevel() << endl;
			
		}else if(cmd == "hint"){
			
		}else if(cmd == "scramble"){
			//check for no moves
			if(!theGame->hint()){
				theGame->scramble();
			}else{
				cout << "There are still moves avaliable" << endl;
			}
		}else if(cmd == "reset"){
			theGame->reset();
		}
		cout << *theGame << endl;
		
	}
	delete theGame;
	// std::cerr << "done" << std::endl;

}