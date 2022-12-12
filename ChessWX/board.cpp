#include "board.h"
#include "util.h"
#include <iostream>
#include <fstream>
int board::arrIndex(Coords coords) {
	return coords.y * height + coords.x;
}

board::board() {
	check = false;
	isAtomic = false;
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
	for (int index = 0; index < width*height; index++){
			piece* curPiece = boardState[index];
			state += pieceType(curPiece);
			state += ",";
			state += pieceColor(curPiece);
			state += ",";
			state += std::to_string(curPiece->hasMoved);
			state += ",";
			state += std::to_string(curPiece->lastMoveDistance);
			state += "\n";
	}
	return state;
}
COLOR getColor(std::string color) {
	if (color == "white") return WHITE;
	else if (color == "black") return BLACK;
	else return UNKNOWN;
}


piece* newPieceFromData(std::string type, COLOR color) {
	if (type == "pawn") return new pawn(color);
	else if (type == "rook") return new rook(color);
	else if (type == "knight") return new knight(color);
	else if (type == "bishop") return new bishop(color);
	else if (type == "queen") return new queen(color);
	else if (type == "king") return new king(color);
	else return new piece(color);
}

piece* makePiece(std::string rowData) {
	std::vector<std::string> pieceAttributes = split(rowData, ',');
	COLOR pieceColor = getColor(pieceAttributes[1]);
	piece* loadedPiece = newPieceFromData(pieceAttributes[0], pieceColor);
	loadedPiece->hasMoved = std::stoi(pieceAttributes[2]);
	loadedPiece->lastMoveDistance =std::stoi(pieceAttributes[3]);
	return loadedPiece;
}
COLOR board::loadSave(std::string saveName) {
	std::ifstream save;
	std::string rowData;
	save.open(saveName);
	int index = 0;
	while (!save.eof() && index < 64) {
		save >> rowData;
		boardState[index] = makePiece(rowData);
		index++;
	}
	std::string color, isAtomic;
	save >> color;
	save >> isAtomic;
	this->isAtomic = stoi(isAtomic);
	if (color == "white") return WHITE;
	else return BLACK;
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
	if (isAtomic) return validMovesAtomic(startPos);
	piece* toMove = boardState[arrIndex(startPos)];
	COLOR enemyColor;
	if (toMove->color == WHITE) enemyColor = BLACK;
	else enemyColor = WHITE;
	std::vector<std::array<int, 2>> potentialMoves = toMove->generateMoves(boardState, lastMoved, startPos.x, startPos.y);
	std::vector<std::array<int, 2>> filteredMoves;

	for (auto move : potentialMoves) {
		int distanceY = abs(move[1] - startPos.y);
		if (toMove->type == KING && distanceY > 1) { 
			if (!canCastle(toMove, startPos, Coords{ move[0],move[1] })) continue;
			if (isCheck(enemyColor)) continue; //King in check can't castle
		}
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
	return filteredMoves;
}

//This function does a preliminary check for king castling. This will not check the final castling Coords, rather the one square before the castle square.
bool board::canCastle(piece *king, Coords startPos, Coords endPos) {
	COLOR enemyColor;
	if (king->color == WHITE) enemyColor = BLACK;
	else enemyColor = WHITE;
	if (endPos.y == 6) {
		endPos.y = 5;
	}
	else if (endPos.y == 2) {
		endPos.y = 3;
	}

	piece* temp = boardState[arrIndex(startPos)];
	piece* tempFinal = boardState[arrIndex(endPos)];
	boardState[arrIndex(startPos)] = new piece(COLOR(UNKNOWN));
	boardState[arrIndex(endPos)] = temp;

	if (isCheck(enemyColor)) {
		boardState[arrIndex(startPos)] = temp;
		boardState[arrIndex(endPos)] = tempFinal; //return board to original state
		return false;
	}
	else {
		boardState[arrIndex(startPos)] = temp;
		boardState[arrIndex(endPos)] = tempFinal; //return board to original state
		return true;

	}
}

std::vector<std::array<int, 2>> board::validMovesAtomic(Coords startPos) {
	piece* toMove = boardState[arrIndex(startPos)];
	COLOR enemyColor;
	if (toMove->color == WHITE) enemyColor = BLACK;
	else enemyColor = WHITE;
	std::vector<std::array<int, 2>> potentialMoves = toMove->generateMoves(boardState, lastMoved, startPos.x, startPos.y);
	std::vector<std::array<int, 2>> filteredMoves;

	Coords kingCoords = findKing(toMove->color);
	if (kingCoords.x == -1 && kingCoords.y == -1) return filteredMoves;


	for (auto move : potentialMoves) {
		piece* finalPosPiece = boardState[arrIndex(Coords{ move[0],move[1] })];
		if (finalPosPiece->color != toMove->color && finalPosPiece->type != PLACEHOLDER && containsOwnKing(move, toMove->color)) continue; //Attacks on enemy pieces which destroy your own king aren't allowed
		if (finalPosPiece->color == toMove->color) continue; //Target position claimed by allied piece; can't move there
		filteredMoves.push_back(move);
	}
	return filteredMoves;
}

bool board::containsOwnKing(std::array<int, 2> move, COLOR color) {
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			Coords newCoords = { move[0] + x, move[1] + y };
			if (isOutOfBounds(newCoords.x, newCoords.y)) continue;
			piece* atCoords = boardState[arrIndex(newCoords)];
			if (atCoords->type == KING && atCoords->color == color) return true;
		}
	}
	return false;
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
	if (isAtomic) {
		moveAtomic(start, end);
		return;
	}
	piece* movedPiece = boardState[arrIndex(start)];
	int distance = abs(start.x - end.x) + abs(start.y - end.y);
	int distanceY = abs(start.y - end.y);
	movedPiece->lastMoveDistance = distance;
	movedPiece->hasMoved = true;

	if (movedPiece->type == PAWN) handlePawn(movedPiece, start, end);
	else if (movedPiece->type == KING && distanceY > 1) castle(movedPiece,end);
	else {
		boardState[arrIndex(end)] = boardState[arrIndex(start)];
	}

	boardState[arrIndex(start)] = new piece(COLOR(UNKNOWN));
	lastMoved = boardState[arrIndex(end)];
	check = this->isCheck(movedPiece->color);

}

void board::moveAtomic(Coords start, Coords end) {
	piece* movedPiece = boardState[arrIndex(start)];
	piece* atEnd = boardState[arrIndex(end)];
	int distance = abs(start.x - end.x) + abs(start.y - end.y);
	int distanceX = abs(start.x - end.x);
	movedPiece->lastMoveDistance = distance;
	movedPiece->hasMoved = true;

	if (movedPiece->type == PAWN) handlePawn(movedPiece, start, end);
	else if (movedPiece->type == KING && distanceX > 1) castle(movedPiece, end);
	else {
		if (atEnd->color != movedPiece->color && atEnd->type != PLACEHOLDER) annihilate(end);
		else boardState[arrIndex(end)] = movedPiece;
	}

	boardState[arrIndex(start)] = new piece(COLOR(UNKNOWN));
	lastMoved = boardState[arrIndex(end)];
}

void board::annihilate(Coords end) {
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			Coords newCoords = { end.x + x, end.y + y };
			piece* atNewCoords = boardState[arrIndex(newCoords)];
			if (isOutOfBounds(newCoords.x, newCoords.y)) continue;
			if (atNewCoords->type == PAWN && (x != 0 || y != 0)) continue; //Destroy the piece at end coordinates regardless if it's a pawn or not
			boardState[arrIndex(newCoords)] = new piece(COLOR(UNKNOWN));
		}
	}
}

bool board::hasKing(COLOR color) {
	Coords kingCoords = findKing(color);
	return !(kingCoords.x == -1 && kingCoords.y == -1);
}

void board::handlePawn(piece* pawn, Coords start, Coords end) {
	//Check for en passant
	if (boardState[arrIndex(end)]->type == PLACEHOLDER && end.x != 0 && end.x != 7) checkEnPassant(pawn, end);


	//Check for promotion
	else if ((pawn->color == WHITE && end.x == 0) || (pawn->color == BLACK && end.x == 7)) {
		boardState[arrIndex(end)] = new queen(COLOR(pawn->color));
	}
	else {
		if (isAtomic && boardState[arrIndex(end)]->type != PLACEHOLDER) annihilate(end);
		else boardState[arrIndex(end)] = pawn;
		
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
			if (isAtomic) {
				boardState[arrIndex(end)] = pawn;
				annihilate(end);
			}
			boardState[arrIndex(enPassant)] = new piece(COLOR(UNKNOWN));
			return;
		}
		else {
			boardState[arrIndex(end)] = pawn;
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
	Coords kingCoords = findKing(enemyColor);

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

	Coords kingCoords = findKing(enemyColor);

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
	if (onlyKingsLeft()) return true;
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

board::Coords board::findKing(COLOR color) {
	Coords kingCoords = Coords{ -1,-1 };
	for (int x = 0; x < width; x++) { //Look for the king on the board
		for (int y = 0; y < height; y++) {
			piece* potentialKing = boardState[arrIndex(Coords{ x,y })];
			if (potentialKing->type == KING && potentialKing->color == color) {
				kingCoords = Coords{ x,y };
				break;
			}
		}
	}
	return kingCoords;
}

bool board::onlyKingsLeft() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Coords atPos = Coords{ x,y };
			piece* pieceAtPos = boardState[arrIndex(atPos)];
			if (pieceAtPos->type != KING && pieceAtPos->type != PLACEHOLDER) return false;
		}
	}
	return true;
}