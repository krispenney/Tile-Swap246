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
	
	//command names
	string switchSquare = "switch";
	string levelup = "levelup";
	string leveldown = "leveldown";
	string hint = "hint";
	string scramble = "scramble";
	string reset = "reset";
	
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
		}else if(cmd == "rename"){
			string old;
			string newName;
			bool success = false;
			
			cin >> old >> newName;
			
			if ((newName != old) &&//prevent same names
				(newName != switchSquare) &&
				(newName != levelup) &&
				(newName != leveldown) &&
				(newName != hint) &&
				(newName != scramble) &&
				(newName != reset)) {
				if (old == switchSquare) {
					switchSquare = newName;
				}else if (old == levelup) {
					levelup = newName;
				}else if (old == leveldown) {
					leveldown = newName;
				}else if (old == hint) {
					hint = newName;
				}else if (old == scramble) {
					scramble = newName;
				}else if (old == reset) {
					reset = newName;
				}
				cout << old << " has been renamed to " << newName << endl;
				success = true;
			}
			
			if (!success) {
				cout << "rename unsuccessful" << endl;
			}
		}else if(cmd == switchSquare){  //needs to check for match
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
		}else if(cmd == levelup){//level up
			if(theGame->getLevel() != MAXLEVELS){
				theGame->changeLevel(true);
				
			}else{
				cout << "No more levels" << endl;
			}
			cout << "Playing level: " << theGame->getLevel() << endl;
			
		}else if(cmd == leveldown){//level down
			if(theGame->getLevel() > 0){
				theGame->changeLevel(false);
				
			}else{
				cout << "No More levels" << endl;
			}
			cout << "Playing level: " << theGame->getLevel() << endl;
			
		}else if(cmd == hint){
			if(!theGame->hint()){//no hint avaliable
				cout << "no moves possible" << endl;
			}
		}else if(cmd == scramble){
			//check for no moves
			if(!theGame->hint()){
				theGame->scramble();
			}else{
				cout << "There are still moves avaliable" << endl;//can't scramble
			}
		}else if(cmd == reset){
			theGame->reset();
		}else if (cmd == "help" or cmd == "?") {
			cout << endl;
			cout << "Welcome to SS5K!" << endl;
			cout << "Availiable commands:" << endl;
			cout << switchSquare << endl;
			cout << "Usage: " << switchSquare << " <row> <column> <direction>" << endl;
			cout << "Note that for directions, 0 is north, 1 is south, 2 is west, and 3 is east." << endl;
			cout << levelup << endl;
			cout << "Increase difficulty to the next level" << endl;
			cout << leveldown << endl;
			cout << "Decrease difficulty to the previous level" << endl;
			cout << hint << endl;
			cout << "Provides a possible next move" << endl;
			cout << scramble << endl;
			cout << "Scrambles the board. Only avaliable when no possible moves" << endl;
			cout << "rename" << endl;
			cout << "Usage: rename <oldName> <newName" << endl;
			cout << "Renames the given command" << endl;
			cout << endl;
		}else{
			cout << "Not a valid move" << endl;
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