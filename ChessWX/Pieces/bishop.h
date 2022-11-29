#pragma once
#include "piece.h"
class bishop : piece
{
public:
	bishop(COLOR color);
	~bishop();
public:
	wxString getDisplayText() override;
};

