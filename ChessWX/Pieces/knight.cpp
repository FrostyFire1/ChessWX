#include "knight.h"
knight::knight(COLOR color) : piece(color){
	displayTextWhite = wxT("♘");
	displayTextBlack = wxT("♞");
}
wxString knight::getDisplayText() {
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}