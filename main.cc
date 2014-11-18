#include <iostream>

#include "board.h"
#include "game.h"
#include "square.h"
#include "textdisplay.h"

using namespace std;

Game * theGame = new Game(10);

int main() {

	cout << theGame;

}