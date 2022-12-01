#include "board.h"

int board::arrIndex(int x, int y) {
	return y * height + x;
}
board::board(){
	this->width = 8;
	this->height = 8;
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
			boardState[arrIndex(x,y)] = new piece(COLOR(WHITE));
		}
	}
}
void board::initBoard() {
	initPawns();
	initMaterial(COLOR(WHITE));
	initMaterial(COLOR(BLACK));
}
void board::initPawns() {

	for (int column = 0; column < 8; column++) {
		boardState[arrIndex(1, column)] = new pawn(COLOR(BLACK)); //Black pawn row
		boardState[arrIndex(6, column)] = new pawn(COLOR(WHITE)); //White pawn row
	}
}
void board::initMaterial(COLOR color) {
	int row;
	if (color == WHITE) row = 7;
	else row = 0;

	boardState[arrIndex(row, 0)] = new rook(color);
	boardState[arrIndex(row, 7)] = new rook(color);

	boardState[arrIndex(row, 1)] = new knight(color);
	boardState[arrIndex(row, 6)] = new knight(color);

	boardState[arrIndex(row, 2)] = new bishop(color);
	boardState[arrIndex(row, 5)] = new bishop(color);

	boardState[arrIndex(row, 3)] = new queen(color);
	boardState[arrIndex(row, 4)] = new king(color);
}