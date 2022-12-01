#pragma once
#include "piece.h"
class knight : public piece
{
public:
	knight(COLOR color);
	~knight();
public:
	wxString getDisplayText() override;
	std::vector<int[2]> generateMoves(piece**, int, int) override;
};

