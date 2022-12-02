#pragma once
#include "piece.h"
class king : public piece
{
public:
	king(COLOR color);
	~king();
public:
	wxString getDisplayText() override;
	std::vector<std::array<int, 2>> generateMoves(piece**, piece*, int, int) override;
};

