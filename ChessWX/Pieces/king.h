#pragma once
#include "piece.h"
class king : piece
{
public:
	king(COLOR color);
	~king();
public:
	wxString getDisplayText() override;
};

