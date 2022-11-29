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