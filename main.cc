#include <iostream>

// #include "board.h"
#include "game.h"
// #include "square.h"
// #include "textdisplay.h"

using namespace std;

Game * theGame = new Game(10);

int main() {

	// std::cerr << "here" << std::endl;
	cout << *theGame << endl;;
	// std::cerr << "done" << std::endl;

}