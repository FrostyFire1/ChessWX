#pragma once
#include "piece.h"
class king : public piece
{
public:
	king(COLOR color);
	~king();
public:
	wxString getDisplayText() override;
};

