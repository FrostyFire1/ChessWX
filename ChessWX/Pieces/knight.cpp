#include "knight.h"
knight::knight(COLOR color) : piece(color){
	displayTextWhite = wxT("♘");
	displayTextBlack = wxT("♞");
}
wxString knight::getDisplayText() {
	if (color == WHITE) return displayTextWhite;
	else return displayTextBlack;
}
std::vector<int[2]> knight::generateMoves(piece** board, int x, int y) {
	std::vector<int[2]> potentialMoves;
	int knightMoves[][2] = { {1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2} }; //Hardcoded knight moves relative to his position on the board
	for (int *move : knightMoves) {
		int newX = x + move[0];
		int newY = y + move[1];
		if (outOfBounds(x, y)) continue;
		potentialMoves.push_back({ newX,newY });
	}
	return potentialMoves;
}