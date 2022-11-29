#include "pawn.h"
pawn::pawn(COLOR color) : piece(color){
	displayTextWhite = wxT("♙");
	displayTextBlack = wxT("♟︎");
}
wxString pawn::getDisplayText(){
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}