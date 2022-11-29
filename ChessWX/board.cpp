#include "board.h"
#include "Pieces/pawn.h"
board::board(int width, int height){
	this->width = width;
	this->height = height;
	boardState = new piece * [width * height];
	initEmpty();
	initBoard();
}

board::~board() {
	delete[] boardState;
}
void board::initEmpty() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			boardState[x * width + y] = new piece(COLOR(WHITE));
		}
	}
}
void board::initBoard() {
	initPawns();
	initWhite();
	initBlack();
}
void board::initPawns() {

	for (int y = 0; y < 8; y++) {
		boardState[1 + y*height] = new pawn(COLOR(BLACK)); //Black pawn row
		boardState[6 + y*height] = new pawn(COLOR(WHITE)); //White pawn row
	}
}
void board::initWhite() {

}
void board::initBlack() {

}