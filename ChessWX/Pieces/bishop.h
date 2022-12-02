#pragma once
#include "piece.h"
class bishop : public piece
{
public:
	bishop(COLOR color);
	~bishop();
public:
	wxString getDisplayText() override;
	std::vector<std::array<int, 2>> generateMoves(piece**, piece*, int, int) override;

};

