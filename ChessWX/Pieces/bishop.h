#pragma once
#include "piece.h"
class bishop : public piece
{
public:
	bishop(COLOR color);
	~bishop();
public:
	wxString getDisplayText() override;

};

