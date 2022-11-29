#include "piece.h"

piece::piece() {
	displayTextWhite = wxT("Unknown");
}
piece::~piece() {

}
wxString piece::getDisplayText() { return displayTextWhite; }