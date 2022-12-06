#include "board.h"
int board::arrIndex(Coords coords) {
	return coords.y * height + coords.x;
}

board::board() {
	check = false;
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

std::string pieceType(piece* piece) {
	switch (piece->type) {
	case PAWN:
		return "pawn";
	case ROOK:
		return "rook";
	case KNIGHT:
		return "knight";
	case BISHOP:
		return "bishop";
	case QUEEN:
		return "queen";
	case KING:
		return "king";
	default:
		return "placeholder";
	}
}

std::string pieceColor(piece* piece) {
	switch (piece->color) {
	case WHITE:
		return "white";
	case BLACK:
		return "black";
	case UNKNOWN:
		return "unknown";
	default:
		return "undefined";
	}
}

std::string board::getState() {
	std::string state = "";
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			piece* curPiece = boardState[arrIndex(Coords{ x,y })];
			state += "{";
			state += pieceType(curPiece);
			state += ",";
			state += pieceColor(curPiece);
			state += ",";
			state += std::to_string(curPiece->hasMoved);
			state += ",";
			state += std::to_string(curPiece->lastMoveDistance);
			state += "}";
			if (y < height - 1) state += ",";
		}
		state += "\n";
	}
	return state;
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

std::vector<std::array<int, 2>> board::validMoves(Coords startPos) {
	piece* toMove = boardState[arrIndex(startPos)];
	COLOR enemyColor;
	if (toMove->color == WHITE) enemyColor = BLACK;
	else enemyColor = WHITE;
	std::vector<std::array<int, 2>> potentialMoves = toMove->generateMoves(boardState, lastMoved, startPos.x, startPos.y);
	std::vector<std::array<int, 2>> filteredMoves;

	for (auto move : potentialMoves) {
		//Simulate the move
		piece* temp = boardState[arrIndex(startPos)];
		piece* tempFinal = boardState[arrIndex(Coords{move[0],move[1]})];
		boardState[arrIndex(startPos)] = new piece(COLOR(UNKNOWN));
		boardState[arrIndex(Coords{ move[0],move[1] })] = temp;

		//After simulating the move check if the enemy has you in check
		if (isCheck(enemyColor)) { 
			boardState[arrIndex(startPos)] = temp;
			boardState[arrIndex(Coords{move[0],move[1]})] = tempFinal; //return board to original state
			continue;
		}
		else {
			boardState[arrIndex(startPos)] = temp;
			boardState[arrIndex(Coords{move[0],move[1]})] = tempFinal; //return board to original state
			filteredMoves.push_back(move);
		}
	}
	return filteredMoves; //TODO: Check for mate, discovery attacks etc.
}

bool board::moveIsValid(Coords startPos, Coords finalPos) {
	std::vector<std::array<int, 2>> validMoves = this->validMoves(startPos);
	for (std::array<int, 2> move : validMoves) {

		if (finalPos.x == move[0] && finalPos.y == move[1]) {
			return true;
		}
	}
	return false;
}

void board::move(Coords start, Coords end) {
	piece* movedPiece = boardState[arrIndex(start)];
	int distance = abs(start.x - end.x) + abs(start.y - end.y);
	int distanceX = abs(start.x - end.x);
	movedPiece->lastMoveDistance = distance;
	movedPiece->hasMoved = true;

	if (movedPiece->type == PAWN) handlePawn(movedPiece, start, end);
	else if (movedPiece->type == KING && distanceX > 1) castle(movedPiece,end);
	else {
		boardState[arrIndex(end)] = boardState[arrIndex(start)];
	}

	boardState[arrIndex(start)] = new piece(COLOR(UNKNOWN));
	lastMoved = boardState[arrIndex(end)];
	check = this->isCheck(movedPiece->color);

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

bool board::isCheck(COLOR color) {
	COLOR enemyColor;
	if (color == WHITE) enemyColor = BLACK;
	else enemyColor = WHITE;
	Coords kingCoords = Coords{ -1,-1 };
	for (int x = 0; x < width; x++) { //Look for the king on the board
		for (int y = 0; y < height; y++) {
			piece* potentialKing = boardState[arrIndex(Coords{ x,y })];
			if (potentialKing->type == KING && potentialKing->color == enemyColor) {
				kingCoords = Coords{ x,y };
				break;
			}
		}
	}

	for (int x = 0; x < width; x++) { //Check every allied piece if they have the king in check
		for (int y = 0; y < height; y++) {

			piece* potentialAlly = boardState[arrIndex(Coords{ x,y })];
			if (potentialAlly->color == color) {
				std::vector<std::array<int, 2>> moveList = potentialAlly->generateMoves(boardState, lastMoved, x, y);
				for (auto move : moveList) {
					if (move[0] == kingCoords.x && move[1] == kingCoords.y) return true;
				}
			}
			
		}
	}


	return false;
}

bool board::isMate(COLOR color) {
	if (!isCheck(color)) return false;
	COLOR enemyColor;
	if (color == WHITE) enemyColor = BLACK;
	else enemyColor = WHITE;

	Coords kingCoords = Coords{ -1,-1 };
	for (int x = 0; x < width; x++) { //Look for the king on the board
		for (int y = 0; y < height; y++) {
			piece* potentialKing = boardState[arrIndex(Coords{ x,y })];
			if (potentialKing->type == KING && potentialKing->color == enemyColor) {
				kingCoords = Coords{ x,y };
				break;
			}
		}
	}

	for (int x = 0; x < width; x++) { //Check every allied piece if they have the king in check
		for (int y = 0; y < height; y++) {

			piece* potentialEnemy = boardState[arrIndex(Coords{ x,y })];
			if (potentialEnemy->color == enemyColor) {
				std::vector<std::array<int, 2>> moveList = this->validMoves(Coords{ x,y }); //Check if there's any valid block
				if (!moveList.empty()) return false;
			}

		}
	}
	return true;
}

bool board::isDraw(COLOR color) {
	COLOR enemyColor;
	if (color == WHITE) enemyColor = BLACK;
	else enemyColor = WHITE;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			piece* potentialEnemy = boardState[arrIndex(Coords{ x,y })];
			if (potentialEnemy->color == enemyColor) {
				std::vector<std::array<int, 2>> moveList = this->validMoves(Coords{ x,y }); //Check if there's any valid moves
				if (!moveList.empty()) return false;
			}

		}
	}
	return true;
}