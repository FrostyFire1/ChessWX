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
	return potentialMoves;
}