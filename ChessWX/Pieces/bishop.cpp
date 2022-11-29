#include "bishop.h"
bishop::bishop(COLOR color) : piece(color) {
	displayTextWhite = wxT("♗");
	displayTextBlack = wxT("♝");
}
wxString bishop::getDisplayText() {
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}