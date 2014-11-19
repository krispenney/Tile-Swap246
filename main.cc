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
	
	// std::cerr << "here" << std::endl;
	cout << *theGame << endl;
	
	while(1){
		
		cin >> cmd;
		if(cin.eof()){
			break;
		}else if(cmd == "switch"){//needs to check for match
			cin >> x >> y >> dir;
			
			if(dir == 0){//north
				if(x-1 < 0){
					cout << "Invalid switch!" << endl;
				}else{
					theGame->swap(x, y, x-1, y);
				}
			}else if(dir == 1){//south
				if(x+1 > 9){
					cout << "Invalid switch!" << endl;
				}else{
					theGame->swap(x, y, x+1, y);
				}
			}else if(dir == 2){//west
				if(y-1 < 0){
					cout << "Invalid switch!" << endl;
				}else{
					theGame->swap(x, y, x, y-1);
				}
				
			}else if(dir == 3){//east
				if(y+1 > 9){
					cout << "Invalid switch!" << endl;
				}else{
					theGame->swap(x, y, x, y+1);
				}
			}
		
		}else if(cmd == "reset"){
			theGame->reset();
		}
		cout << *theGame << endl;
		
	}
	delete theGame;
	// std::cerr << "done" << std::endl;

}