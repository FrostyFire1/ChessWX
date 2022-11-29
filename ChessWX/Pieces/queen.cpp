#include "queen.h"
queen::queen() {
	displayTextWhite = wxT("♕");
	displayTextBlack = wxT("♛");
}
wxString queen::getDisplayText() { return displayTextWhite; }