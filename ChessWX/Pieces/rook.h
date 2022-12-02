#pragma once
#include "piece.h"
class rook : public piece{
public:
	rook(COLOR color);
	~rook();
public:
	wxString getDisplayText() override;
	std::vector<std::array<int, 2>> generateMoves(piece**, piece*, int, int) override;

};

