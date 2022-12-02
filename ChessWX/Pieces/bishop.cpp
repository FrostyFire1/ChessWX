#include "bishop.h"
bishop::bishop(COLOR color) : piece(color) {
	type = BISHOP;
	displayTextWhite = wxT("♗");
	displayTextBlack = wxT("♝");
	pieceImageWhite.LoadFile("img/bishop.png", wxBITMAP_TYPE_PNG);
	pieceImageBlack.LoadFile("img/bishop.png", wxBITMAP_TYPE_PNG);

}
wxBitmap bishop::getPieceImage() {
	if (this->color == WHITE) return pieceImageWhite;
	else return pieceImageBlack;
}
wxString bishop::getDisplayText() {
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}

std::vector<std::array<int, 2>> bishop::generateMoves(piece** board, piece* _, int x, int y) {
	std::vector<std::array<int, 2>>potentialMoves;
	int steps[][2] = { {1,1},{1,-1},{-1,1},{-1,-1} };
	int newX, newY;
	for (int* step : steps) {
		newX = x + step[0];
		newY = y + step[1];
		while (!isOutOfBounds(newX, newY)) {
			piece* atDestination = board[arrIndex(newX, newY, 8)];
			if (atDestination->color == this->color) break;

			potentialMoves.push_back({ newX,newY });
			if (atDestination->type != PLACEHOLDER && atDestination->color != this->color) break;

			newX += step[0];
			newY += step[1];
		}
	}
	return potentialMoves;
}