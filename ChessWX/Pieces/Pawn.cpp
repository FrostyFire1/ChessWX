#include "pawn.h"
pawn::pawn(COLOR color) : piece(color){
	type = PAWN;
	hasMoved = false;
	displayTextWhite = wxT("♙");
	displayTextBlack = wxT("♟︎");
	pieceImageWhite.LoadFile("img/pawn.png", wxBITMAP_TYPE_PNG);
	pieceImageBlack.LoadFile("img/pawn.png", wxBITMAP_TYPE_PNG);
}

wxBitmap pawn::getPieceImage() {
	if (this->color == WHITE) return pieceImageWhite;
	else return pieceImageBlack;
}
wxString pawn::getDisplayText(){
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}
std::vector<std::array<int, 2>> pawn::generateMoves(piece** board, piece* lastMoved, int x, int y) {
	int direction;
	if (this->color == WHITE) direction = -1;
	else direction = 1;
	std::vector<std::array<int, 2>> pawnMoves;
	std::vector<std::array<int, 2>> filteredMoves;

	if (!isOutOfBounds(x + direction, y) && board[arrIndex(x + direction, y, 8)]->type == PLACEHOLDER) {
		pawnMoves.push_back({ x + direction, y + 0 }); //Can move 1 rank forward
		if (!isOutOfBounds(x + 2 * direction, y) && board[arrIndex(x + 2 * direction, y, 8)]->type == PLACEHOLDER) {
			if (!hasMoved) pawnMoves.push_back({ x + 2 * direction,y + 0 }); //First move can also be 2 ranks forward 
		}
	}
	
	if (!isOutOfBounds(x + direction, y + 1) && board[arrIndex(x + direction, y + 1, 8)]->type != PLACEHOLDER) {
		pawnMoves.push_back({ x + direction, y + 1 }); //Can attack diagonally
	}

	if (!isOutOfBounds(x + direction, y - 1) && board[arrIndex(x + direction, y - 1, 8)]->type != PLACEHOLDER) {
		pawnMoves.push_back({ x + direction, y - 1 }); //Can attack diagonally in the other direction
	}


	if (!isOutOfBounds(x, y + 1)) { //En passant to the right
		piece* curPiece = board[arrIndex(x, y + 1, 8)];
		if (curPiece->color != this->color && curPiece->type == PAWN && curPiece->lastMoveDistance == 2 && curPiece == lastMoved)
			pawnMoves.push_back({ x + direction, y + 1 });
	}
	if (!isOutOfBounds(x, y - 1)) { //En passant to the left
		piece* curPiece = board[arrIndex(x, y - 1, 8)];
		if (curPiece->color != this->color && curPiece->type == PAWN && curPiece->lastMoveDistance == 2 && curPiece == lastMoved)
			pawnMoves.push_back({ x + direction, y - 1 });
	}

	for (auto move : pawnMoves) {
		if (isOutOfBounds(move[0], move[1])) continue;
		if (board[arrIndex(move[0], move[1], 8)]->color == this->color) continue;
		filteredMoves.push_back(move);
	}
	return filteredMoves;
}