#pragma once
#include "piece.h"
class knight : public piece
{
public:
	knight(COLOR color);
	~knight();
public:
	wxString getDisplayText() override;
	wxBitmap getPieceImage() override;
	std::vector<std::array<int, 2>> generateMoves(piece**, piece*, int, int) override;
};

