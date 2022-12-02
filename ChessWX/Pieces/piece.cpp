#include "piece.h"

piece::piece(COLOR color) {
	type = PLACEHOLDER;
	hasMoved = false;
	displayTextWhite = wxT("");
	displayTextBlack = wxT("");
	this->color = color;
}
piece::~piece() {

}
wxString piece::getDisplayText() { 
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}
std::vector<std::array<int, 2>> piece::generateMoves(piece** _,piece* __, int ___, int ____) {
	std::vector<std::array<int, 2>> moves;
	return moves;
}
int piece::arrIndex(int x, int y, int height) {
	return y * height + x;
}
wxBitmap piece::getPieceImage() {
	return pieceImageWhite;
}