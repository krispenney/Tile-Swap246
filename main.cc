#include <iostream>

// #include "board.h"
#include "game.h"
#include <ctime>
#include <cstring>
#include <fstream>
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
	bool customScript = false;
	int seed = time(NULL);
	int startlevel = 0;
	string scriptfile = "sequence.txt";
	ifstream *fin = NULL;
	//get command line arguments
	const char *text = "-text";
	const char *nSeed = "-seed";
	const char *sFile = "-scriptfile";
	const char *sLevel = "-startlevel";
	
	//read cmd line args
	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i], text) == 0){//graphics
			graphics = false;
		}else if(strcmp(argv[i], nSeed) == 0){//set seed
			seed = atoi(argv[i+1]);
			i++;
		}else if(strcmp(argv[i], sFile) == 0){//scriptfile
			fin = new ifstream(argv[i+1]);
			customScript = true;
			i++;
		}else if(strcmp(argv[i], sLevel) == 0){//startlevel
			startlevel = atoi(argv[i+1]);
			i++;
		}
	}
	
	
	/*cerr <<"------------" << endl;
	cerr << graphics << endl;
	cerr << seed << endl;
	cerr << scriptfile << endl;
	cerr << startlevel << endl;
	cerr <<"------------" << endl;*/
	
	if(fin == NULL){//sequence.txt
		
		fin = new ifstream(scriptfile.c_str());
	}
	
	Game *theGame = new Game(10, startlevel, seed, fin, graphics, customScript);
	
	// std::cerr << "here" << std::endl;
	cout << *theGame << endl;
	
	//enters game
	while(1){
		
		cin >> cmd;
		if(cin.eof()){
			break;
		}else if(cmd == "switch"){  //needs to check for match
			cin >> x >> y >> dir;
			bool match = false;
			int chain = 0;
			
			if(theGame->checkSwap(x, y, dir)){//checks for match
				match = theGame->checkMatch(chain);
			}
			
			if (match) {
				theGame->decMoves();
				while (match) {
					chain++;
					// cout << *theGame << endl;
					match = theGame->checkMatch(chain);
					// match = false;
					// cerr << "I HAVE A LOOPING MATCH~~~" << endl;
				}
			} else {
				cerr << "No match made - Please try again" << endl;//no match - swap back
				theGame->checkSwap(x, y, dir);
			}
		}else if(cmd == "levelup"){//level up
			if(theGame->getLevel() != MAXLEVELS){
				theGame->changeLevel(true);
				
			}else{
				cout << "No more levels" << endl;
			}
			cout << "Playing level: " << theGame->getLevel() << endl;
			
		}else if(cmd == "leveldown"){//level down
			if(theGame->getLevel() > 0){
				theGame->changeLevel(false);
				
			}else{
				cout << "No More levels" << endl;
			}
			cout << "Playing level: " << theGame->getLevel() << endl;
			
		}else if(cmd == "hint"){
			if(!theGame->hint(true)){//no hint avaliable
				cout << "no moves possible" << endl;
			}
		}else if(cmd == "scramble"){
			//check for no moves
			if(!theGame->hint(false)){
				theGame->scramble();
			}else{
				cout << "There are still moves avaliable" << endl;//can't scramble
			}
		}else if(cmd == "reset"){
			theGame->reset();
		}
		

		if (theGame->levelWon()) {
			cout << "LEVEL UP!!" << endl;
			if(theGame->getLevel() != MAXLEVELS){
				theGame->changeLevel(true);
				
			} else {
				cout << endl << endl;
				cout << "CONGRATULATIONS" << endl;
				cout << "YOU WON!" << endl;
				break;
			}
		}

		cout << *theGame << endl;


	}
	delete theGame;
	// std::cerr << "done" << std::endl;

}