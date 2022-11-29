#pragma once
#include "piece.h"
class bishop : piece
{
public:
	bishop();
	~bishop();
public:
	wxString getDisplayText() override;
};

