#include "rook.h"
rook::rook(COLOR color) : piece(color){
	type = ROOK;
	displayTextWhite = wxT("♖");
	displayTextBlack = wxT("♜");
}
wxString rook::getDisplayText() { 
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}

std::vector<std::array<int, 2>> rook::generateMoves(piece** board, piece* _, int x, int y) {
	std::vector<std::array<int, 2>>potentialMoves;
	int steps[][2] = { {1,0},{-1,0},{0,1},{0,-1} };
	int newX, newY;
	for (int *step : steps) {
		newX = x + step[0];
		newY = y + step[1];
		while (!isOutOfBounds(newX, newY)) {
			piece* atDestination = board[arrIndex(newX, newY,8)];
			if (atDestination->color == this->color) break;

			potentialMoves.push_back({ newX,newY });
			if (atDestination->color != UNKNOWN) break;

			newX += step[0];
			newY += step[1];
		}
	}
	return potentialMoves;
}
