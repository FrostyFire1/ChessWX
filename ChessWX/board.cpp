#include "board.h"


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
	initMaterial(COLOR(WHITE));
	initMaterial(COLOR(BLACK));
}
void board::initPawns() {

	for (int column = 0; column < 8; column++) {
		boardState[1 + column*height] = new pawn(COLOR(BLACK)); //Black pawn row
		boardState[6 + column*height] = new pawn(COLOR(WHITE)); //White pawn row
	}
}
void board::initMaterial(COLOR color) {
	int row;
	if (color == WHITE) row = 7;
	else row = 0;

	boardState[row + 0 * height] = new rook(color);
	boardState[row + 7 * height] = new rook(color);

	boardState[row + 1 * height] = new knight(color);
	boardState[row + 6 * height] = new knight(color);

	boardState[row + 2 * height] = new bishop(color);
	boardState[row + 5 * height] = new bishop(color);

	boardState[row + 3 * height] = new queen(color);
	boardState[row + 4 * height] = new king(color);
}