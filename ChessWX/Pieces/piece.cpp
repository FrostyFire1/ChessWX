#include "piece.h"

piece::piece(COLOR color) {
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
std::vector<int[2]> piece::generateMoves(piece** _, int __, int ___) {
	std::vector<int[2]> moves;
	return moves;
}
int piece::arrIndex(int x, int y, int height) {
	return y * height + x;
}