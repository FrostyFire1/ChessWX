#include "board.h"
#include "Pieces/pawn.h"
board::board(int width, int height){
	boardState = new piece * [width * height];
	boardState[0*width + 0] = new pawn();
}

board::~board() {
	delete[] boardState;
}