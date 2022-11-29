#pragma once
#include "piece.h"
class queen : piece
{
public:
	queen();
	~queen();
public:
	wxString getDisplayText() override;
};

