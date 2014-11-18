#include "board.cc"

using namespace std;

Board::Board(){
	
}

Board::~Board(){
	delete td;
	delete theBoard;
}

void init(int level, string filename = ""){
	
	string zeroFName = "sequence.txt";
	bool locked = false;
	char type;
	int colour;
	
	delete theBoard;
	delete td;
	
	if(level == 0){
		ifstream fin(zeroFName);
		
		/* colours:    Squares:
		 * White: 0    Basic: _
		 * Red: 1      Lateral: h
		 * Green: 2    Upright: v
		 * Blue: 3     Unstable: b
		 *             Psychedelic: p
		 */
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 10; j++){
				fin >> type >> colour;
				
				theBoard[i][j] = new Square(colour, type, false);
				td->update(i, j, colour + '0', type);
			}
		}
		
	}else if(level == 1){
		
		/*if(filename != ""){ add in scriptfile later
			
		}else{
			
		}*/
		
		
		
	}else if(level == 2){
		
		/*if(filename != ""){ add in scriptfile later
			
		 }else{
			
		 }*/
		
		
		
	}
	//more as levels increase
}

void swap(Square * s1, Square * s2){
	int tmpColour = s1->colour;
	int tmpType = s2->colour;
	
	s1->colour = s2->colour;
	s1->type = s2->type;
	
	s2->colour = tmpColour;
	s2->type = tmpType;
	
	//td->notify(); notify board
	
}

ostream &operator<<(ostream &out, const Board &b){
	out << b.td;
	return out;
}