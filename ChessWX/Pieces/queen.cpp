#include "queen.h"
queen::queen(COLOR color) : piece(color){
	type = QUEEN;
	displayTextWhite = wxT("♕");
	displayTextBlack = wxT("♛");
}
wxString queen::getDisplayText() { 
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}