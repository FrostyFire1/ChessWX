#include "board.h"
int board::arrIndex(Coords coords) {
	return coords.y * height + coords.x;
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
			boardState[arrIndex(Coords{ x,y })] = new piece(COLOR(UNKNOWN));
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
		boardState[arrIndex(Coords{ 1, column })] = new pawn(COLOR(BLACK)); //Black pawn row
		boardState[arrIndex(Coords{ 6, column })] = new pawn(COLOR(WHITE)); //White pawn row
	}
}

void board::initMaterial(COLOR color) {
	int row;
	if (color == WHITE) row = 7;
	else row = 0;

	boardState[arrIndex(Coords{row, 0})] = new rook(color);
	boardState[arrIndex(Coords{row, 7})] = new rook(color);

	boardState[arrIndex(Coords{row, 1})] = new knight(color);
	boardState[arrIndex(Coords{row, 6})] = new knight(color);

	boardState[arrIndex(Coords{row, 2})] = new bishop(color);
	boardState[arrIndex(Coords{row, 5})] = new bishop(color);

	boardState[arrIndex(Coords{row, 3})] = new queen(color);
	boardState[arrIndex(Coords{row, 4})] = new king(color);
}

bool board::moveIsValid(Coords startPos, Coords finalPos) {
	std::vector<int[2]> potentialMoves = boardState[arrIndex(startPos)]->generateMoves(boardState);
	return true;
}
void board::move(Coords start, Coords end) {
	boardState[arrIndex(end)] = boardState[arrIndex(start)];
	boardState[arrIndex(start)] = new piece(COLOR(UNKNOWN));
}