#include "pawn.h"
pawn::pawn() : piece(){
	displayTextWhite = wxT("♙");
	displayTextBlack = wxT("♟︎");
}
wxString pawn::getDisplayText(){ return displayTextWhite; }