#include "rook.h"
rook::rook() {
	displayTextWhite = wxT("♖");
	displayTextBlack = wxT("♜");
}
wxString rook::getDisplayText() { return displayTextWhite; }