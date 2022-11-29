#pragma once
#include "piece.h"
class rook : public piece{
public:
	rook(COLOR color);
	~rook();
public:
	wxString getDisplayText() override;
};

