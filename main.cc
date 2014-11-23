#include <iostream>

// #include "board.h"
#include "game.h"
#include <ctime>
#include <cstring>
// #include "square.h"
// #include "textdisplay.h"

using namespace std;



int main(int argc, char *argv[]) {
	
	string cmd;
	int x;
	int y;
	int dir;
	const int MAXLEVELS = 2;
	bool graphics = true;
	int seed = time(NULL);
	int startlevel = 0;
	string scriptfile = "";
	
	//get command line arguments
	const char *text = "-text";
	const char *nSeed = "-seed";
	const char *sFile = "-scriptfile";
	const char *sLevel = "-startlevel";
	
	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i], text) == 0){//graphics
			graphics = false;
		}else if(strcmp(argv[i], nSeed) == 0){//set seed
			seed = atoi(argv[i+1]);
			i++;
		}else if(strcmp(argv[i], sFile) == 0){//scriptfile
			scriptfile = argv[i+1];
			i++;
		}else if(strcmp(argv[i], sLevel) == 0){//startlevel
			startlevel = atoi(argv[i+1]);
			i++;
		}
	}
	
	//need to implement custom scriptfile and graphics(later)
	
	/*cerr <<"------------" << endl;
	cerr << graphics << endl;
	cerr << seed << endl;
	cerr << scriptfile << endl;
	cerr << startlevel << endl;
	cerr <<"------------" << endl;*/
	
	Game *theGame = new Game(10, startlevel, seed, scriptfile, graphics);
	
	// std::cerr << "here" << std::endl;
	cout << *theGame << endl;
	
	//enters game
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
					// match = false;
					chain++;
				}
				
			} else {
				// cerr << "no match made plz" << endl;
				// NO MATCH MADE, revert last move
			}
			theGame->decMoves();
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
			if(!theGame->hint(true)){
				cout << "no moves possible" << endl;
			}
		}else if(cmd == "scramble"){
			//check for no moves
			if(!theGame->hint(false)){
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