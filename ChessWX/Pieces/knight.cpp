#include "knight.h"
knight::knight(COLOR color) : piece(color){
	type = KNIGHT;
	displayTextWhite = wxT("♘");
	displayTextBlack = wxT("♞");
	pieceImageWhite.LoadFile("img/knight.png", wxBITMAP_TYPE_PNG);
	pieceImageBlack.LoadFile("img/knightBlack.png", wxBITMAP_TYPE_PNG);

}

wxBitmap knight::getPieceImage() {
	if (this->color == WHITE) return pieceImageWhite;
	else return pieceImageBlack;
}

wxString knight::getDisplayText() {
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}
std::vector<std::array<int, 2>> knight::generateMoves(piece** board,piece* _, int x, int y) {
	std::vector<std::array<int, 2>>potentialMoves;
	int knightMoves[][2] = { {1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2} }; //Hardcoded knight moves relative to his position on the board
	for (int *move : knightMoves) {
		int newX = x + move[0];
		int newY = y + move[1];
		std::array<int, 2> curMove = { newX,newY };

		if (isOutOfBounds(newX, newY)) continue;
		if (board[arrIndex(newX, newY, 8)]->color == this->color) continue; //Can't move into your own pieces
		potentialMoves.push_back(curMove);
	}
	return potentialMoves;
}