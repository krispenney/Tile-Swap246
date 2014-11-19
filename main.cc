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
			bool match = false;;
				if(dir == 0){//north
					if(x-1 < 0){
						cout << "Invalid switch!" << endl;
					}else{
						theGame->swap(x, y, x-1, y);
						match = theGame->checkMatch();
					}
				}else if(dir == 1){//south
					if(x+1 > 9){
						cout << "Invalid switch!" << endl;
					}else{
						theGame->swap(x, y, x+1, y);
						match = theGame->checkMatch();
					}
				}else if(dir == 2){//west
					if(y-1 < 0){
						cout << "Invalid switch!" << endl;
					}else{
						theGame->swap(x, y, x, y-1);
						match = theGame->checkMatch();
					}
					
				}else if(dir == 3){//east
					if(y+1 > 9){
						cout << "Invalid switch!" << endl;
					}else{
						theGame->swap(x, y, x, y+1);
						match = theGame->checkMatch();
					}
				}

			if (match) {
				while (match) {

					match = theGame->checkMatch();
				}
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
			
		}else if(cmd == "reset"){
			theGame->reset();
		}
		cout << *theGame << endl;
		
	}
	delete theGame;
	// std::cerr << "done" << std::endl;

}