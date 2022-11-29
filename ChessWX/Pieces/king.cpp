#include "king.h"
king::king() {
	displayTextWhite = wxT("♔");
	displayTextBlack = wxT("♚");
}
wxString king::getDisplayText() { return displayTextWhite; }