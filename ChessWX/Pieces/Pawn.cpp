#include "piece.h"
#include "pawn.h"
pawn::pawn() : piece(){
	displayText = "pawn";
}
std::string pawn::getDisplayText(){ return displayText; }