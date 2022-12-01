#include "king.h"
king::king(COLOR color) : piece(color){
	type = KING;
	displayTextWhite = wxT("♔");
	displayTextBlack = wxT("♚");
}
wxString king::getDisplayText() { 
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}