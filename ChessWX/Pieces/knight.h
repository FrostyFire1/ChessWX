#pragma once
#include "piece.h"
class knight : public piece
{
public:
	knight(COLOR color);
	~knight();
public:
	wxString getDisplayText() override;
	std::vector<std::array<int, 2>> generateMoves(piece**, int, int) override;
};

