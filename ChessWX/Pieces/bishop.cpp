#include "bishop.h"
bishop::bishop() {
	displayTextWhite = wxT("♗");
	displayTextBlack = wxT("♝");
}
wxString bishop::getDisplayText() { return displayTextWhite; }