#include "king.h"
king::king(COLOR color) : piece(color){
	type = KING;
	displayTextWhite = wxT("♔");
	displayTextBlack = wxT("♚");
}
wxString king::getDisplayText() { 
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}

std::vector<std::array<int, 2>> king::generateMoves(piece** board, piece* _, int x, int y) {
	std::vector<std::array<int, 2>>potentialMoves;
	int kingMoves[][2] = { {1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1} }; //Hardcoded king moves 
	for (int* move : kingMoves) {
		int newX = x + move[0];
		int newY = y + move[1];
		std::array<int, 2> curMove = { newX,newY };

		if (isOutOfBounds(newX, newY)) continue;
		if (board[arrIndex(newX, newY, 8)]->color == this->color) continue; //Can't move into your own pieces
		potentialMoves.push_back(curMove);
	}
	//check for castling
	if (!(this->hasMoved)) {
		piece* possibleRookRight;
		piece* possibleRookLeft;
		int row;

		if (this->color == WHITE) row = 7;
		else row = 0;
		possibleRookRight = board[arrIndex(row, 7, 8)];
		possibleRookLeft = board[arrIndex(row, 0, 8)];

		if (possibleRookRight->type == ROOK && !(possibleRookRight->hasMoved)) {
			if (board[arrIndex(row, 6, 8)]->type == PLACEHOLDER && 
				board[arrIndex(row, 5, 8)]->type == PLACEHOLDER) {
				potentialMoves.push_back({ row,6 });
			}
		}

		if (possibleRookLeft->type == ROOK && !(possibleRookLeft->hasMoved)) {
			if (board[arrIndex(row, 1, 8)]->type == PLACEHOLDER && 
				board[arrIndex(row, 2, 8)]->type == PLACEHOLDER &&
				board[arrIndex(row, 3, 8)]->type == PLACEHOLDER) {
				potentialMoves.push_back({ row,2 });
			}
		}
	}
	return potentialMoves;
}