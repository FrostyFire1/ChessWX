#include "board.h"
int board::arrIndex(Coords coords) {
	return coords.y * height + coords.x;
}

board::board() {
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

	boardState[arrIndex(Coords{ row, 0 })] = new rook(color);
	boardState[arrIndex(Coords{ row, 7 })] = new rook(color);

	boardState[arrIndex(Coords{ row, 1 })] = new knight(color);
	boardState[arrIndex(Coords{ row, 6 })] = new knight(color);

	boardState[arrIndex(Coords{ row, 2 })] = new bishop(color);
	boardState[arrIndex(Coords{ row, 5 })] = new bishop(color);

	boardState[arrIndex(Coords{ row, 3 })] = new queen(color);
	boardState[arrIndex(Coords{ row, 4 })] = new king(color);
}

std::vector<std::array<int, 2>> board::validMoves(Coords startPos, Coords finalPos) {
	std::vector<std::array<int, 2>> potentialMoves = boardState[arrIndex(startPos)]->generateMoves(boardState, lastMoved, startPos.x, startPos.y);
	return potentialMoves; //TODO: Check for mate, discovery attacks etc.
}

bool board::moveIsValid(Coords startPos, Coords finalPos) {
	std::vector<std::array<int, 2>> validMoves = this->validMoves(startPos, finalPos);
	for (std::array<int, 2> move : validMoves) {
		//check if move is in list of valid moves
		if (finalPos.x == move[0] && finalPos.y == move[1]) {
			return true;
		}
	}
	return false;
}

void board::move(Coords start, Coords end) {
	piece* movedPiece = boardState[arrIndex(start)];
	int distance = abs(start.x - end.x) + abs(start.y - end.y);


	if (movedPiece->type == PAWN) handlePawn(movedPiece, start, end);
	else if (movedPiece->type == KING && distance > 1) castle(movedPiece,end);
	else {
		boardState[arrIndex(end)] = boardState[arrIndex(start)];
	}

	movedPiece->lastMoveDistance = distance;
	movedPiece->hasMoved = true;
	boardState[arrIndex(start)] = new piece(COLOR(UNKNOWN));
	lastMoved = boardState[arrIndex(end)];
}

void board::handlePawn(piece* pawn, Coords start, Coords end) {
	//Check for en passant
	if (boardState[arrIndex(end)]->type == PLACEHOLDER) checkEnPassant(pawn, end);


	//Check for promotion
	if ((pawn->color == WHITE && end.x == 0) || (pawn->color == BLACK && end.x == 7)) {
		boardState[arrIndex(end)] = new queen(COLOR(pawn->color));
	}
	else {
		boardState[arrIndex(end)] = pawn;
	}
}

void board::checkEnPassant(piece* pawn, Coords end) {
	piece* potentialPawn;
	int direction;
	if (pawn->color == WHITE) direction = 1;
	else direction = -1;
	Coords enPassant = Coords{ end.x + direction, end.y};

	if (!isOutOfBounds(enPassant.x, enPassant.y)){
		potentialPawn = boardState[arrIndex(enPassant)];
		if (potentialPawn->type == PAWN && potentialPawn->color != pawn->color && potentialPawn == lastMoved) {
			boardState[arrIndex(enPassant)] = new piece(COLOR(UNKNOWN));
			return;
		}
	}
	

}

void board::castle(piece* king, Coords end) {
	if (end.y == 6) {
		piece* temp = boardState[arrIndex(Coords{ end.x, 6 })];
		piece* rook = boardState[arrIndex(Coords{ end.x, 7 })];
		boardState[arrIndex(end)] = king;
		boardState[arrIndex(Coords{ end.x, 5})] = rook;
		boardState[arrIndex(Coords{ end.x, 7 })] = new piece(COLOR(UNKNOWN));
	}
	else if (end.y == 2) {
		piece* temp = boardState[arrIndex(Coords{ end.x, 6 })];
		piece* rook = boardState[arrIndex(Coords{ end.x, 0 })];
		boardState[arrIndex(end)] = king;
		boardState[arrIndex(Coords{ end.x, 3 })] = rook;
		boardState[arrIndex(Coords{ end.x, 0 })] = new piece(COLOR(UNKNOWN));
	}
}