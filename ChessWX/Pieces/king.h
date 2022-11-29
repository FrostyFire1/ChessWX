#pragma once
#include "piece.h"
class king : piece
{
public:
	king();
	~king();
public:
	wxString getDisplayText() override;
};

