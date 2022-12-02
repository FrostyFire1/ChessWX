#pragma once
#include "piece.h"
class queen : public piece
{
public:
	queen(COLOR color);
	~queen();
public:
	wxString getDisplayText() override;
	std::vector<std::array<int, 2>> generateMoves(piece**, piece*, int, int) override;

};

