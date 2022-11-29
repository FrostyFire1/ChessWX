#include "knight.h"
knight::knight() {
	displayTextWhite = wxT("♘");
	displayTextBlack = wxT("♞");
}
wxString knight::getDisplayText() { return displayTextWhite; }