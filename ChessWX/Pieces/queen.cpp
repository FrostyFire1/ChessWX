#include "queen.h"
queen::queen(COLOR color) : piece(color){
	displayTextWhite = wxT("♕");
	displayTextBlack = wxT("♛");
}
wxString queen::getDisplayText() { 
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}