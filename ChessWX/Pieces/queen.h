#pragma once
#include "piece.h"
class queen : public piece
{
public:
	queen(COLOR color);
	~queen();
public:
	wxString getDisplayText() override;
};

