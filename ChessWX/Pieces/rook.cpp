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