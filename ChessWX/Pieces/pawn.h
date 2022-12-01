#pragma once
#include "piece.h"
#include <string>
class pawn : public piece{
public:
	pawn(COLOR color);
	~pawn();
public:
	wxString getDisplayText() override;
	std::vector<std::array<int, 2>> generateMoves(piece**,piece*, int, int) override;
};