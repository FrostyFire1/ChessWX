#pragma once
#include "piece.h"
class queen : piece
{
public:
	queen(COLOR color);
	~queen();
public:
	wxString getDisplayText() override;
};

